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
#include <QStandardItemModel>
#include <QWidget>
#include <QTimer>
#include <QtDebug>

#include <gsl/gsl_matrix.h>

#include <matrix.h>
#include "meteorLoader.h"
#include "meteorWriter.h"
#include "meteorRadioNetworkForm.h"
#include "meteorRadioStationForm.h"
#include "meteorRadioStation.h"
#include "meteorRadioStationsModel.h"
#include "meteorRadioStationsFactory.h"
#include "meteorRadioController.h"
#include "meteorTraceGenerationFactory.h"
#include <meteorTraceChannel.h>
#include <meteorReportForm.h>

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
    _mRadioC( nullptr ),
    _mTraceGenFactory( nullptr ),
    _messCount( new int ),
    _allBytesCount( new int ),
    _dTimeStart( QDateTime() ),
    _dTimeFinish( QDateTime() ),
    _tUpdate( new QTimer ),
    _aveDataTime( 0.0 ),
    _stDataTime( 0.0 ),
    _distModel( nullptr ) {
    *_messCount.data() = 0;
    *_allBytesCount.data() = 0;
}

meteorRadioStationsFactory::~meteorRadioStationsFactory() {
    qDebug() << __PRETTY_FUNCTION__;
    //_mReportForm->deleteLater();
    delete _tUpdate;
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
    QSharedPointer< meteorRadioStation > mRadioStation = wIndex.data( Qt::UserRole+2 ).value< QSharedPointer< meteorRadioStation >>();
    _mWriter->deleteStation( mRadioStation );
    int iRow = wIndex.row();
    stationsModel->removeRows( iRow, 1, wIndex.parent() );
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

void meteorRadioStationsFactory::startModelling( QVector< QSharedPointer< meteorRadioStation > > stations, double distMin, double distMax, double distStep, int nStations, double aveMeteorAriseFreq, double aveMeteorTraceTime, double meteorTraceTimeSt, double aveSignalAmpl, double aveMessageLength, double messageSt, double messSpeed, double elevMin, double elevMax, double scatterMin, double scatterMax ) {
    int n = stations.size();
    QObject::connect( _tUpdate, &QTimer::timeout, this, &meteorRadioStationsFactory::updateResults );
    _tUpdate->start( 30000 );
    qDebug() << __PRETTY_FUNCTION__ << n << distMin << distMax << distStep << nStations << aveMeteorAriseFreq << aveMeteorTraceTime << meteorTraceTimeSt << aveSignalAmpl << aveMessageLength << messageSt << messSpeed;
    emit sendTraceParameters( aveMeteorAriseFreq, aveMeteorTraceTime, meteorTraceTimeSt, aveSignalAmpl, elevMin, elevMax, scatterMin, scatterMax );
     if( n < 2 ) {
        QWidget* pW = qobject_cast< QWidget* >(this->sender());
        QMessageBox::warning(pW, tr("Stochastic modelling"), tr("Any station is needed"), QMessageBox::Ok );
        return;
    }
    if( _distModel )
        delete _distModel;
    _distModel = new QStandardItemModel( n*(n-1)/2, 3 );
    _distModel->setHeaderData( 0, Qt::Horizontal, tr("Distance"), Qt::DisplayRole );
    _distModel->setHeaderData( 1, Qt::Horizontal, tr("Average processing time"), Qt::DisplayRole );
    _distModel->setHeaderData( 2, Qt::Horizontal, tr("Standard processing time"), Qt::DisplayRole );
    meteorReportForm* mReportForm = new meteorReportForm;
    mReportForm->setModel( _distModel );
    QObject::connect( this, &meteorRadioStationsFactory::sendReport, mReportForm, &meteorReportForm::updateReport );
    QObject::connect( this, &QObject::destroyed, mReportForm, &QObject::deleteLater );
    Matrix mDist( 0.0, n, n );
    bool isConnectivity = false;
    for( int i=0; i<n; i++ ) {
        for( int j=0; j<i; j++ ) {
            double wdist = _mLoader->distance( stations[i], stations[j], -1 );
            bool isStationsAvail = (wdist >= distMin && wdist <= distMax );
            isConnectivity = isConnectivity || isStationsAvail;
            mDist(i, j) = wdist;
            mDist(j, i) = wdist;
            if( isStationsAvail ) {
                stations[i]->addAddress( stations[j]->getAddress().toStdString() );
                stations[j]->addAddress( stations[i]->getAddress().toStdString() );
            }
            qDebug() << __PRETTY_FUNCTION__ << i << j << wdist;
        }
    }
    if( !isConnectivity ) {
        QWidget* pW = qobject_cast< QWidget* >(this->sender());
        QMessageBox::warning(pW, tr("Stochastic modelling"), tr("No connectivity between stations"), QMessageBox::Ok );
        return;
    }
    _mTraceGenFactory->setDistances( mDist );
    _mRadioC.clear();
    _mRadioC = QSharedPointer<meteorRadioController> ( new meteorRadioController( messSpeed, stations, _messCount, _allBytesCount ) );
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
    QObject::connect( this,
                      &meteorRadioStationsFactory::sendMeteorChannel,
                      _mRadioC.get(),
                      &meteorRadioController::getMeteorTrace,
                      Qt::DirectConnection
            );
    _dTimeStart = QDateTime::currentDateTimeUtc();
    updateResults();
    emit signalModStart();
    emit viewRadioParam( mReportForm );
//    _mRadioC->startMess();
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
    _dTimeFinish = QDateTime::currentDateTimeUtc();
     qDebug() << __PRETTY_FUNCTION__ << _dTimeStart.msecsTo( _dTimeFinish )/1000.0;
     QObject::disconnect( _tUpdate );
     emit signalModStop();
}

void meteorRadioStationsFactory::setTraceGenerationFactory( meteorTraceGenerationFactory* trGenF ) {
    _mTraceGenFactory = trGenF;
}

void meteorRadioStationsFactory::sendChannelToStations( QSharedPointer< meteorTraceChannel > mtc ) {
    if( mtc.isNull() )
        return;
    emit sendMeteorChannel( mtc );
}

void meteorRadioStationsFactory::updateResults() {
    QDateTime cDateTime = QDateTime::currentDateTimeUtc();
    double aveAriseTime = _mTraceGenFactory->getAveAriseTime();
    double aveDurationTime = _mTraceGenFactory->getAveDurationTime();
    double avePower = _mTraceGenFactory->getAvePower();
    _aveDataTime = aveAriseTime;
    _stDataTime = _mTraceGenFactory->getStArise();
    vector< double > dist = _mTraceGenFactory->getDistances();
    vector< double > aveTime = _mTraceGenFactory->getAveTime();
    vector< double > stTime = _mTraceGenFactory->getStTime();
    int nd = dist.size();
    for(int i=0; i<nd; i++) {
        _distModel->setData( _distModel->index(i, 0), dist[i], Qt::DisplayRole );
        _distModel->setData( _distModel->index(i, 1), aveTime[i], Qt::DisplayRole );
        _distModel->setData( _distModel->index(i, 2), stTime[i], Qt::DisplayRole );
    }
    emit sendReport( *_messCount, *_allBytesCount, _mTraceGenFactory->getTracesNumber(), _dTimeStart.msecsTo( cDateTime ), aveDurationTime, aveAriseTime, avePower, _aveDataTime, _stDataTime );
}

double meteorRadioStationsFactory::getAveTime() const {
    return _aveDataTime;
}

double meteorRadioStationsFactory::getStTime() const {
    return _stDataTime;
}

