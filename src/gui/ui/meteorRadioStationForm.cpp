/*
 * @brief Форма добавления/редактирования параметров станций связи
 * meteorRadioStationForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QMdiSubWindow>
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
    QMdiSubWindow* mdiChild = qobject_cast<QMdiSubWindow*>(this->parentWidget());
    QWidget::close();
    if( mdiChild )
        mdiChild->close();
}

void meteorRadioStationForm::saveStation() {
    if( _meteorRadioStation.isNull() )
        return;

    qint16 sNumb = _UI->lEStationNumber->text().toLongLong();
    _meteorRadioStation->setStationNumber( sNumb );
    DistributionFunc idDistr = (DistributionFunc)_UI->cbDistribFunc->currentData( ).toInt();
    double lon = _UI->lELongitude->text().toDouble();
    double lat = _UI->lELatitude->text().toDouble();
    _meteorRadioStation->setLongitude( lon );
    _meteorRadioStation->setLatitude( lat );
    meteorRadioStationType msType = (meteorRadioStationType)_UI->cbStationType->currentData( ).toInt();
    _meteorRadioStation->setType( msType );

    emit saveMeteorRadioStation( _meteorRadioStation );
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

    QMap< QString, meteorRadioStationType > tItems;
    tItems.insert( tr("Subscriber station"), meteorRadioStationType::mSubscriber );
    tItems.insert( tr("Intermediate station"), meteorRadioStationType::mIntermediate );
    for( QMap< QString, meteorRadioStationType >::const_iterator pt = tItems.constBegin();
            pt != tItems.constEnd();
            pt++ )
        _UI->cbStationType->addItem( pt.key(), pt.value() );
    _UI->cbStationType->setCurrentIndex( 1 );
}
