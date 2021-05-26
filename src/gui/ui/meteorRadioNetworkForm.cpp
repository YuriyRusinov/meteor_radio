/*
 * @brief Форма задания исходных параметров станций и метеорных потоков
 * meteorRadioNetworkForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QModelIndex>
#include <QValidator>
#include <QDoubleValidator>
#include <QtDebug>
#include <meteorRadioStation.h>
#include "meteorRadioNetworkForm.h"
#include "ui_meteor_radio_network_form.h"

meteorRadioNetworkForm::meteorRadioNetworkForm( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _UI( new Ui::meteor_radio_network_form ) {
    _UI->setupUi( this );

    init();

    QObject::connect( _UI->tbAddStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::addStation );
    QObject::connect( _UI->tbEditStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::editStation );
    QObject::connect( _UI->tbDelStation, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::delStation );
    QObject::connect( _UI->tbRefresh, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::refreshStations );
    QObject::connect( _UI->pbStartModel, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::startModelling );
    QObject::connect( _UI->pbStopModel, &QAbstractButton::clicked, this, &meteorRadioNetworkForm::stopModelling );
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
    QAbstractItemModel* stationsModel = _UI->tvStationsList->model();
    emit addMRStation( stationsModel );
}

void meteorRadioNetworkForm::editStation() {
    qDebug() << __PRETTY_FUNCTION__;
    QAbstractItemModel* stationsModel = _UI->tvStationsList->model();
    QItemSelectionModel* selModel = _UI->tvStationsList->selectionModel();
    if( stationsModel == nullptr || selModel == nullptr )
        return;
    QItemSelection statSel = selModel->selection();
    QModelIndexList stIndexes = statSel.indexes();
    if( stIndexes.isEmpty() ) {
        QMessageBox::warning( this, tr("Edit station"), tr("Select station for edit"), QMessageBox::Ok );
        return;
    }
    QModelIndex sIndex = stIndexes.at( 0 );
    emit editMRStation( sIndex, stationsModel );
}

void meteorRadioNetworkForm::delStation() {
    qDebug() << __PRETTY_FUNCTION__;
    QAbstractItemModel* stationsModel = _UI->tvStationsList->model();
    QItemSelectionModel* selModel = _UI->tvStationsList->selectionModel();
    if( stationsModel == nullptr || selModel == nullptr )
        return;
    QItemSelection statSel = selModel->selection();
    QModelIndexList stIndexes = statSel.indexes();
    if( stIndexes.isEmpty() ) {
        QMessageBox::warning( this, tr("Remove station"), tr("Select station for remove"), QMessageBox::Ok );
        return;
    }
    QModelIndex sIndex = stIndexes.at( 0 );
    QMessageBox::StandardButton res = QMessageBox::question( this, tr("Remove station"), tr("Do you really want to delete station ?") );
    if( res != QMessageBox::Yes )
        return;
    emit delMRStation( sIndex, stationsModel );
}

void meteorRadioNetworkForm::refreshStations() {
    emit refreshStationModel( _UI->tvStationsList );
}

void meteorRadioNetworkForm::startModelling() {
    qDebug() << __PRETTY_FUNCTION__;
    QAbstractItemModel* stationsModel = _UI->tvStationsList->model();
    int n = stationsModel->rowCount();
    QVector<QSharedPointer< meteorRadioStation > > mStations;
    for( int i=0; i<n; i++ ) {
        Qt::CheckState isSel;
        QModelIndex wIndex = stationsModel->index(i, 0);
        isSel = stationsModel->data( wIndex, Qt::CheckStateRole ).value< Qt::CheckState >();
        if( isSel == Qt::Checked ) {
            QSharedPointer< meteorRadioStation > wStation = stationsModel->data( wIndex, Qt::UserRole+2 ).value< QSharedPointer< meteorRadioStation > >();
            mStations.append( wStation );
            qDebug() << __PRETTY_FUNCTION__ << wStation->getId();
        }
    }
    if( mStations.size() < 2 ) {
        QMessageBox::warning( this, tr("Meteor modelling"), tr("Any base station is needed"), QMessageBox::Ok );
        return;
    }
    double distMin = _UI->lEMinLength->text().toDouble();
    double distMax = _UI->lEMaxLength->text().toDouble();
    double distStep = _UI->dSBStep->value();
    int stNumber = _UI->spStatNumb->value();
    double mAveFreq = _UI->lEAMathExp->text().toDouble();
    double mTraceEx = _UI->lETimeExistance->text().toDouble();
    double mTraceSt = _UI->lETimeExistanceSt->text().toDouble();
    double mSignalAmpl = _UI->lESignalAmplitude->text().toDouble();
    double messLen = _UI->lEMessageLength->text().toDouble();
    double messLenSt = _UI->lEMessageStandard->text().toDouble();
    double trafficSpeed = _UI->lEMessageSpeed->text().toDouble();
    double mElevMin = _UI->lEElevationMin->text().toDouble();
    double mElevMax = _UI->lEElevationMax->text().toDouble();
    double mScatterMin = _UI->lEScatteringMin->text().toDouble();
    double mScatterMax = _UI->lEScatteringMax->text().toDouble();
    int nTraces = _UI->lETracesNumb->text().toInt();
    emit beginModelling( mStations, distMin, distMax, distStep, stNumber, mAveFreq, mTraceEx, mTraceSt, mSignalAmpl, messLen, messLenSt, trafficSpeed, mElevMin, mElevMax, mScatterMin, mScatterMax );
}

void meteorRadioNetworkForm::close() {
    stopModelling();
    QMdiSubWindow* mdiChild = qobject_cast<QMdiSubWindow*>(this->parentWidget());
    QWidget::close();
    if( mdiChild )
        mdiChild->close();
}

void meteorRadioNetworkForm::init() {
    QValidator* valMinLength = new QDoubleValidator( 20.0, 2000.0, 8, this );
    _UI->lEMinLength->setValidator( valMinLength );
    _UI->lEMinLength->setText( QString::number(700.0) );

    QValidator* valMaxLength = new QDoubleValidator( 20.0, 2000.0, 8, this );
    _UI->lEMaxLength->setValidator( valMaxLength );
    _UI->lEMaxLength->setText( QString::number( 1200.0 ) );

    QValidator* valAMathExp = new QDoubleValidator( 20.0, 100.0, 8, this );
    _UI->lEAMathExp->setValidator( valAMathExp );
    _UI->lEAMathExp->setText( QString::number( 60.0 ) );

    QValidator* valTimeEx = new QDoubleValidator( 20.0, 1000.0, 8, this );
    _UI->lETimeExistance->setValidator( valTimeEx );
    _UI->lETimeExistance->setText( QString::number( 500.0 ) );

    QValidator* valTimeExSt = new QDoubleValidator( 0.0, 1000.0, 8, this );
    _UI->lETimeExistanceSt->setValidator( valTimeExSt );
    _UI->lETimeExistanceSt->setText( QString::number( 150.0 ) );

    QValidator* valSignalAmpl = new QDoubleValidator( 0.0, 10000.0, 8, this );
    _UI->lESignalAmplitude->setValidator( valSignalAmpl );
    _UI->lESignalAmplitude->setText( QString::number( 200.0 ) );

    QValidator* valMessLength = new QDoubleValidator( 0.0, 10000.0, 8, this );
    _UI->lEMessageLength->setValidator( valMessLength );
    _UI->lEMessageLength->setText( QString::number( 5000.0 ) );

    QValidator* valMessSt = new QDoubleValidator( 0.0, 4000.0, 8, this );
    _UI->lEMessageStandard->setValidator( valMessSt );
    _UI->lEMessageStandard->setText( QString::number( 300.0 ) );

    QValidator* valMessSpeed = new QDoubleValidator( 0.0, 10000.0, 8, this );
    _UI->lEMessageSpeed->setValidator( valMessSpeed );
    _UI->lEMessageSpeed->setText( QString::number( 5.0 ) );

    _UI->tvStationsList->setSelectionMode( QAbstractItemView::ExtendedSelection );

    _UI->tbRefresh->setToolTip( tr("Refresh stations") );

    QValidator* valElevMin = new QDoubleValidator( -10.0, 100.0, 8, this );
    _UI->lEElevationMin->setValidator( valElevMin );
    _UI->lEElevationMin->setText( QString::number( 0.0 ) );

    QValidator* valElevMax = new QDoubleValidator( -10.0, 100.0, 8, this );
    _UI->lEElevationMax->setValidator( valElevMax );
    _UI->lEElevationMax->setText( QString::number( 90.0 ) );

    QValidator* valScatterMin = new QDoubleValidator( 0.0, 10.0, 8, this );
    _UI->lEScatteringMin->setValidator( valScatterMin );
    _UI->lEScatteringMin->setText( QString::number( 0.0 ) );

    QValidator* valScatterMax = new QDoubleValidator( 0.0, 50.0, 8, this );
    _UI->lEScatteringMax->setValidator( valScatterMax );
    _UI->lEScatteringMax->setText( QString::number( 45.0 ) );

    QValidator* valTracesNumber = new QIntValidator( 1, 100000, this );
    _UI->lETracesNumb->setValidator( valTracesNumber );
    _UI->lETracesNumb->setText( QString::number( 10000 ) );
}

void meteorRadioNetworkForm::stopModelling() {
    emit finishModelling();
}
