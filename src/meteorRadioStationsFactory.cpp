/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QWidget>
#include <QtDebug>
#include "meteorLoader.h"
#include "meteorWriter.h"
#include "meteorRadioNetworkForm.h"
#include "meteorRadioStationsFactory.h"

QWidget* meteorRadioStationsFactory::GUIStationsParameters( QWidget* parent, Qt::WindowFlags flags ) const {
    meteorRadioNetworkForm* w = new meteorRadioNetworkForm( parent, flags );
    QObject::connect( w, &meteorRadioNetworkForm::addMRStation, this, &meteorRadioStationsFactory::addMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::editMRStation, this, &meteorRadioStationsFactory::editMeteorStation );
    QObject::connect( w, &meteorRadioNetworkForm::delMRStation, this, &meteorRadioStationsFactory::delMeteorStation );
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
