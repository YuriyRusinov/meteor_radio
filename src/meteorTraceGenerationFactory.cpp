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
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ),
    _mRSF( nullptr ),
    _mTraceController( new meteorTraceController ) {
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
