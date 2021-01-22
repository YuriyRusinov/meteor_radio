/*
 * @brief Форма добавления/редактирования параметров станций связи
 * meteorRadioStationForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QMdiSubWindow>
#include <QSharedPointer>

#include <randomNumbGenerator.h>
#include <uniRandomNumbGenerator.h>
#include <expRandomNumbGenerator.h>
#include <gaussianRandomNumbGenerator.h>
#include <rayleighRandomNumbGenerator.h>

#include <meteorRadioStation.h>
#include "meteorDelegate.h"
#include "randomParametersModel.h"
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
    QString sAddr = _UI->lEStationAddress->text();
    _meteorRadioStation->setAddress( sAddr );
    DistributionFunc idDistr = (DistributionFunc)_UI->cbDistribFunc->currentData( ).toInt();
    double lon = _UI->lELongitude->text().toDouble();
    double lat = _UI->lELatitude->text().toDouble();
    _meteorRadioStation->setLongitude( lon );
    _meteorRadioStation->setLatitude( lat );
    _meteorRadioStation->setSrid( 4326 );
    double freq = _UI->lEStationFrequency->text().toDouble();
    _meteorRadioStation->setFrequency( freq );
    meteorRadioStationType msType = (meteorRadioStationType)_UI->cbStationType->currentData( ).toInt();
    _meteorRadioStation->setType( msType );
    QSharedPointer< randomNumbersGenerator > rng = nullptr;
    switch( idDistr ) {
        case DistributionFunc::_Uniform: rng = QSharedPointer< randomNumbersGenerator > (new uniRandomNumbersGenerator ); break;
        case DistributionFunc::_Exponential: rng = QSharedPointer< randomNumbersGenerator >( new expRandomNumbersGenerator ); break;
        case DistributionFunc::_Gaussian: rng = QSharedPointer< randomNumbersGenerator > (new gaussianRandomNumbersGenerator ); break;
        case DistributionFunc::_Rayleigh: rng = QSharedPointer< randomNumbersGenerator > (new rayleighRandomNumbersGenerator ); break;
        default: break;
    }
    QAbstractItemModel* rParamMod = _UI->tvParameters->model();
    int n = rParamMod->rowCount();
    for (int i=0; i<n; i++) {
        double val = rParamMod->data( rParamMod->index( i, 0 ) ).toDouble();
        rng->addParamValue( val );
    }
    _meteorRadioStation->setMessagesGen( rng.get() );

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
    dItems.insert( tr("Rayleigh"), DistributionFunc::_Rayleigh );
    for( QMap<QString, DistributionFunc>::const_iterator pd = dItems.constBegin();
            pd != dItems.constEnd();
            pd++ ) {
        _UI->cbDistribFunc->addItem( pd.key(), pd.value() );
    }

    QSharedPointer< randomNumbersGenerator > rng;
    if( _meteorRadioStation->getMessagesGen() == nullptr ) {
        rng = QSharedPointer< randomNumbersGenerator > ( new rayleighRandomNumbersGenerator );
        rng->addParamValue(1.0);
        _UI->cbDistribFunc->setCurrentIndex( 2 );
    }
    else
        rng = QSharedPointer< randomNumbersGenerator > ( _meteorRadioStation->getMessagesGen()->clone().get() );
    QAbstractItemModel* rpModel = new randomParametersModel( rng );
    QAbstractItemDelegate* mDeleg = new meteorDelegate();
    _UI->tvParameters->setModel( rpModel );
    _UI->tvParameters->setSelectionMode( QAbstractItemView::SingleSelection );
    _UI->tvParameters->setItemDelegate( mDeleg );
    QMap< QString, meteorRadioStationType > tItems;
    tItems.insert( tr("Subscriber station"), meteorRadioStationType::mSubscriber );
    tItems.insert( tr("Intermediate station"), meteorRadioStationType::mIntermediate );
    for( QMap< QString, meteorRadioStationType >::const_iterator pt = tItems.constBegin();
            pt != tItems.constEnd();
            pt++ )
        _UI->cbStationType->addItem( pt.key(), pt.value() );
    _UI->cbStationType->setCurrentIndex( 1 );

    _UI->lEStationNumber->setText( QString::number( _meteorRadioStation->getStationNumber() ) );
    QValidator* snVal = new QIntValidator( 1, 100, this );
    _UI->lEStationNumber->setValidator( snVal );
    _UI->lEStationAddress->setText( _meteorRadioStation->getAddress() );
}
