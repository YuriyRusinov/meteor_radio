/*
 * @brief Форма добавления/редактирования параметров станций связи
 * meteorRadioStationForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <randomNumbGenerator.h>
#include <meteorRadioStation.h>
#include "meteorRadioStationForm.h"
#include "ui_meteor_radio_station_form.h"

meteorRadioStationForm::meteorRadioStationForm( QSharedPointer< meteorRadioStation > mrs, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _meteorRadioStation( mrs ),
    _UI( new Ui::meteor_radio_station_form ) {
    _UI->setupUi( this );
    this->init();

    QObject::connect( _UI->cbDistribFunc, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&meteorRadioStationForm::distribFuncChanged) );
    QObject::connect( _UI->pbApply, &QPushButton::clicked, this, &meteorRadioStationForm::saveStation );
    QObject::connect( _UI->pbOk, &QPushButton::clicked, this, &meteorRadioStationForm::accept );
    QObject::connect( _UI->pbCancel, &QPushButton::clicked, this, &meteorRadioStationForm::close );
}

meteorRadioStationForm::~meteorRadioStationForm() {
    delete _UI;
}

void meteorRadioStationForm::distribFuncChanged(int index) {
}

void meteorRadioStationForm::close() {
}

void meteorRadioStationForm::saveStation() {
}

void meteorRadioStationForm::accept() {
    saveStation();
    close();
}

void meteorRadioStationForm::init() {
    QMap<QString, DistributionFunc> dItems;
    dItems.insert( tr("Uniform"), DistributionFunc::_Uniform );
    dItems.insert( tr("Exponential"), DistributionFunc::_Exponential );
    dItems.insert( tr("Gaussian"), DistributionFunc::_Gaussian );
    for( QMap<QString, DistributionFunc>::const_iterator pd = dItems.constBegin();
            pd != dItems.constEnd();
            pd++ ) {
        _UI->cbDistribFunc->addItem( pd.key(), pd.value() );
    }
}
