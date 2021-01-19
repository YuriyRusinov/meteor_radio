/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QMessageBox>
#include <QSharedPointer>
#include <QWidget>
#include <QtDebug>
#include "meteorLoader.h"
#include "meteorWriter.h"
#include "meteorRadioNetworkForm.h"
#include "meteorRadioStationForm.h"
#include "meteorRadioStation.h"
#include "meteorRadioStationsModel.h"
#include "meteorRadioStationsFactory.h"

QWidget* meteorRadioStationsFactory::GUIStationsParameters( QWidget* parent, Qt::WindowFlags flags ) {
    meteorRadioNetworkForm* w = new meteorRadioNetworkForm( parent, flags );
    meteorRadioStationsModel* mrsm = new meteorRadioStationsModel;
    w->setStationsModel( mrsm );
    QObject::connect( w, &meteorRadioNetworkForm::addMRStation, this, &meteorRadioStationsFactory::addMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::editMRStation, this, &meteorRadioStationsFactory::editMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::delMRStation, this, &meteorRadioStationsFactory::delMeteorStation );
    emit viewRadioParam( w );
    return w;
}

meteorRadioStationsFactory::meteorRadioStationsFactory( meteorLoader* ml, meteorWriter* mw, QObject* parent )
    : QObject( parent ),
    _mLoader( QSharedPointer< meteorLoader >( ml ) ),
    _mWriter( QSharedPointer< meteorWriter >( mw ) ) {
}

meteorRadioStationsFactory::~meteorRadioStationsFactory() {}

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
    Q_UNUSED( wIndex );
    Q_UNUSED( stationsModel );
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
