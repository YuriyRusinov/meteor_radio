/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemView>
#include <QMessageBox>
#include <QSharedPointer>
#include <QWidget>
#include <QtDebug>

#include <gsl/gsl_matrix.h>

#include "meteorLoader.h"
#include "meteorWriter.h"
#include "meteorRadioNetworkForm.h"
#include "meteorRadioStationForm.h"
#include "meteorRadioStation.h"
#include "meteorRadioStationsModel.h"
#include "meteorRadioStationsFactory.h"
#include "meteorRadioController.h"

QWidget* meteorRadioStationsFactory::GUIStationsParameters( QWidget* parent, Qt::WindowFlags flags ) {
    meteorRadioNetworkForm* w = new meteorRadioNetworkForm( parent, flags );
    QVector< QSharedPointer< meteorRadioStation > > mStations = _mLoader->loadStations();
    meteorRadioStationsModel* mrsm = new meteorRadioStationsModel (mStations);
    w->setStationsModel( mrsm );
    QObject::connect( w, &meteorRadioNetworkForm::addMRStation, this, &meteorRadioStationsFactory::addMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::editMRStation, this, &meteorRadioStationsFactory::editMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::delMRStation, this, &meteorRadioStationsFactory::delMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::refreshStationModel, this, &meteorRadioStationsFactory::refreshStations );
    QObject::connect( w,
                      &meteorRadioNetworkForm::beginModelling,
                      this,
                      &meteorRadioStationsFactory::startModelling );
    QObject::connect( w,
                      &meteorRadioNetworkForm::finishModelling,
                      this,
                      &meteorRadioStationsFactory::stopModelling );
    emit viewRadioParam( w );
    return w;
}

meteorRadioStationsFactory::meteorRadioStationsFactory( meteorLoader* ml, meteorWriter* mw, QObject* parent )
    : QObject( parent ),
    _mLoader( QSharedPointer< meteorLoader >( ml ) ),
    _mWriter( QSharedPointer< meteorWriter >( mw ) ),
    _mRadioC( nullptr ) {
}

meteorRadioStationsFactory::~meteorRadioStationsFactory() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioStationsFactory::addMeteorStation( QAbstractItemModel* stationsModel ) {
    qDebug() << __PRETTY_FUNCTION__;
    if( stationsModel == nullptr )
        return;
    QSharedPointer< meteorRadioStation > mRadioStation ( new meteorRadioStation );
    meteorRadioStationForm* mrsf = new meteorRadioStationForm( mRadioStation );
    emit viewRadioParam( mrsf );
    QObject::connect( mrsf,
                      &meteorRadioStationForm::saveMeteorRadioStation,
                      this,
                      &meteorRadioStationsFactory::saveStationToDb );
}

void meteorRadioStationsFactory::editMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel ) {
    qDebug() << __PRETTY_FUNCTION__;
    QSharedPointer< meteorRadioStation > mRadioStation = wIndex.data( Qt::UserRole+2 ).value< QSharedPointer< meteorRadioStation >>();
    Q_UNUSED( stationsModel );
    meteorRadioStationForm* mrsf = new meteorRadioStationForm( mRadioStation );
    emit viewRadioParam( mrsf );
    QObject::connect( mrsf,
                      &meteorRadioStationForm::saveMeteorRadioStation,
                      this,
                      &meteorRadioStationsFactory::saveStationToDb );
}

void meteorRadioStationsFactory::delMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel ) {
    qDebug() << __PRETTY_FUNCTION__;
    Q_UNUSED( wIndex );
    Q_UNUSED( stationsModel );
}

void meteorRadioStationsFactory::saveStationToDb( QSharedPointer< meteorRadioStation > mrs ) {
    qDebug() << __PRETTY_FUNCTION__ << mrs.isNull();
    if( mrs.isNull() )
        return;
    int res;
    if( mrs->getId() <= 0 )
        res = _mWriter->insertStation( mrs );
    else
        res = _mWriter->updateStation( mrs );

    if( res < 0 ) {
        QWidget* pWidget = qobject_cast< QWidget* >(this->sender() );
        QMessageBox::warning(pWidget, tr("Store station"), tr("Cannot save meteor radio station, DB Error"), QMessageBox::Ok );
        return;
    }
}

void meteorRadioStationsFactory::startModelling( QVector< QSharedPointer< meteorRadioStation > > stations, double distMin, double distMax, double aveMeteorAriseFreq, double aveMeteorTraceTime, double meteorTraceTimeSt, double aveMessageLength, double messageSt, double messSpeed ) {
    int n = stations.size();
    qDebug() << __PRETTY_FUNCTION__ << n << distMin << distMax << aveMeteorAriseFreq << aveMeteorTraceTime << meteorTraceTimeSt << aveMessageLength << messageSt << messSpeed;
    if( n < 2 ) {
        QWidget* pW = qobject_cast< QWidget* >(this->sender());
        QMessageBox::warning(pW, tr("Stochastic modelling"), tr("More than 2 stations needed"), QMessageBox::Ok );
        return;
    }

    gsl_matrix * mDist = gsl_matrix_alloc(n, n);
    bool isConnectivity = false;
    for( int i=0; i<n; i++ ) {
        for( int j=0; j<i; j++ ) {
            double wdist = _mLoader->distance( stations[i], stations[j] );
            bool isStationsAvail = (wdist >= distMin && wdist <= distMax );
            isConnectivity = isConnectivity || isStationsAvail;
            gsl_matrix_set( mDist, i, j, wdist );
            gsl_matrix_set( mDist, j, i, wdist );
            if( isStationsAvail ) {
                stations[i]->addAddress( stations[j]->getAddress().toStdString() );
                stations[j]->addAddress( stations[i]->getAddress().toStdString() );
            }
            qDebug() << __PRETTY_FUNCTION__ << i << j << wdist;
        }
        gsl_matrix_set( mDist, i, i, 0.0 );
    }
    if( !isConnectivity ) {
        QWidget* pW = qobject_cast< QWidget* >(this->sender());
        QMessageBox::warning(pW, tr("Stochastic modelling"), tr("No connectivity between stations"), QMessageBox::Ok );
        gsl_matrix_free( mDist );
        return;
    }
    _mRadioC.clear();
    _mRadioC = QSharedPointer<meteorRadioController> ( new meteorRadioController( stations ) );
    QObject::connect( this,
                      &meteorRadioStationsFactory::signalModStart,
                      _mRadioC.get(),
                      &meteorRadioController::startMess
            );
    QObject::connect( this,
                      &meteorRadioStationsFactory::signalModStop,
                      _mRadioC.get(),
                      &meteorRadioController::stopMess
            );
    emit signalModStart();
//    _mRadioC->startMess();

    gsl_matrix_free( mDist );
}

void meteorRadioStationsFactory::refreshStations( QAbstractItemView* stView ) {
    QAbstractItemModel* oldModel = stView->model();
    QVector< QSharedPointer< meteorRadioStation > > mStations = _mLoader->loadStations();
    meteorRadioStationsModel* mrsm = new meteorRadioStationsModel (mStations);
    stView->setModel( mrsm );
    if( oldModel && oldModel != mrsm )
        delete oldModel;
}

void meteorRadioStationsFactory::stopModelling() {
    qDebug() << __PRETTY_FUNCTION__;
    emit signalModStop();
}
