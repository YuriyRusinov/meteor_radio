/*
 * @brief Форма задания исходных параметров станций и метеорных потоков
 * meteorRadioNetworkForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QMdiSubWindow>
#include <QtDebug>
#include "meteorRadioNetworkForm.h"
#include "ui_meteor_radio_network_form.h"

meteorRadioNetworkForm::meteorRadioNetworkForm( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _UI( new Ui::meteor_radio_network_form ) {
    _UI->setupUi( this );

    QObject::connect( _UI->tbAddStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::addStation );
    QObject::connect( _UI->tbEditStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::editStation );
    QObject::connect( _UI->tbDelStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::delStation );
    QObject::connect( _UI->pbStartModel, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::startModelling );
    QObject::connect( _UI->pbClose, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::close );
}

meteorRadioNetworkForm::~meteorRadioNetworkForm() {
    delete _UI;
}

void meteorRadioNetworkForm::setStationsModel( QAbstractItemModel* stationsModel ) {
    QAbstractItemModel* oldModel = _UI->tvStationsList->model();
    _UI->tvStationsList->setModel( stationsModel );
    if( oldModel != nullptr && oldModel != stationsModel )
        delete oldModel;
}

void meteorRadioNetworkForm::addStation() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioNetworkForm::editStation() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioNetworkForm::delStation() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioNetworkForm::startModelling() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioNetworkForm::close() {
    QMdiSubWindow* mdiChild = qobject_cast<QMdiSubWindow*>(this->parentWidget());
    QWidget::close();
    if( mdiChild )
        mdiChild->close();
}
