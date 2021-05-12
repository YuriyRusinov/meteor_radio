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
    _traceCounter( new int (0) ),
    _mTraceController( new meteorTraceController( _traceCounter ) ),
    _aveMeteorDurationTraceTime( 0.0 ),
    _aveMeteorAriseTime( 0.0 ),
    _aveMeteorTracePower( 0.0 ) {
    QObject::connect( _mTraceController, &meteorTraceController::sendTraceChannel, this, &meteorTraceGenerationFactory::retransmitMeteorTrace, Qt::DirectConnection );
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {
    qDebug() << __PRETTY_FUNCTION__ << *_traceCounter;
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
    qDebug() << __PRETTY_FUNCTION__ << *_traceCounter;
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
    _aveMeteorAriseTime += mtc->getAriseTime();
    _aveMeteorDurationTraceTime += mtc->getTimeTrace();
    _aveMeteorTracePower += mtc->getChannelPower();
    emit sendTrace( mtc );
}

int meteorTraceGenerationFactory::getTracesNumber() const {
    if( _traceCounter.isNull() )
        return -1;

    return *_traceCounter;
}

double meteorTraceGenerationFactory::getAveAriseTime() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorAriseTime/(*_traceCounter );
}

double meteorTraceGenerationFactory::getAveDurationTime() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorDurationTraceTime/(*_traceCounter );
}

double meteorTraceGenerationFactory::getAvePower() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorTracePower/(*_traceCounter );
}
