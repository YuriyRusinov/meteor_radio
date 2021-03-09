/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>

#include <meteorTraceChannel.h>
#include "meteorTraceGenerationFactory.h"
#include "meteorTraceController.h"
#include "meteorRadioStationsFactory.h"

QSharedPointer< meteorTraceChannel > meteorTraceGenerationFactory::generate() const {
    return nullptr;
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ),
    _mRSF( nullptr ),
    _mTraceController( new meteorTraceController ) {
    QObject::connect( _mTraceController, &meteorTraceController::sendTraceChannel, this, &meteorTraceGenerationFactory::retransmitMeteorTrace, Qt::DirectConnection );
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceController->stopGenerate();
    delete _mTraceController;//->deleteLater();
}

void meteorTraceGenerationFactory::setStationFactory( meteorRadioStationsFactory* rsf ) {
    _mRSF = rsf;
    QObject::connect( _mRSF,
                      &meteorRadioStationsFactory::signalModStop,
                      this,
                      &meteorTraceGenerationFactory::stopTraceGen );

    QObject::connect( _mRSF,
                      &meteorRadioStationsFactory::sendTraceParameters,
                      this,
                      &meteorTraceGenerationFactory::setTraceParameters );

    QObject::connect( this,
                      &meteorTraceGenerationFactory::sendTrace,
                      _mRSF,
                      &meteorRadioStationsFactory::sendChannelToStations,
                      Qt::DirectConnection );
}

void meteorTraceGenerationFactory::stopTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceController->stopGenerate();
}

void meteorTraceGenerationFactory::setTraceParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
    qDebug() << __PRETTY_FUNCTION__ << _ariseMathExp << _existanceTimeMathExp << _existanceTimeSt << _aveAmpl;
    _mTraceController->setTraceGenParameters( _ariseMathExp, _existanceTimeMathExp, _existanceTimeSt,_aveAmpl );
    _mTraceController->startGenerate();
}

void meteorTraceGenerationFactory::retransmitMeteorTrace( QSharedPointer< meteorTraceChannel > mtc ) {
    qDebug() << __PRETTY_FUNCTION__;
    emit sendTrace( mtc );
}
