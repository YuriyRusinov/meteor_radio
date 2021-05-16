/*
 * @brief Класс генерации метеорных следов для станций метеорной связи
 * meteorTraceWorker.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QTimer>
#include <QtDebug>

#include <gaussianRandomNumbGenerator.h>
#include <expRandomNumbGenerator.h>
#include <uniRandomNumbGenerator.h>
#include <randomNumbGenerator.h>

#include "meteorTraceChannel.h"
#include "meteorTraceWorker.h"

meteorTraceWorker::meteorTraceWorker( QSharedPointer< int > tracesCounter, double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, QObject* parent )
    : QObject( parent ),
    _tracesCounter( tracesCounter ),
    _tMeteorTrace( nullptr ),
    _isTracesRunning( false ),
    _ariseMathExp( ariseM ),
    _existanceTimeMathExp( existanceTime ),
    _existanceTimeSt( existanceTimeSt ),
    _aveAmpl( aveAmpl ), 
    _ariseRng( new expRandomNumbersGenerator ),
    _dtRng( new gaussianRandomNumbersGenerator ),
    _powerRng( new expRandomNumbersGenerator ),
    _elevRng( new uniRandomNumbersGenerator ),
    _scatterRng( new uniRandomNumbersGenerator ) {
    qDebug() << __PRETTY_FUNCTION__;
}

meteorTraceWorker::~meteorTraceWorker() {
    qDebug() << __PRETTY_FUNCTION__;
    delete _tMeteorTrace;
    _ariseRng.reset();
    _dtRng.reset();
    _powerRng.reset();
    _elevRng.reset();
    _scatterRng.reset();
}

void meteorTraceWorker::generateMeteorTraces() {
//    shared_ptr< randomNumbersGenerator > rng ( new gaussianRandomNumbersGenerator );
    if( !_tMeteorTrace ) {
        _tMeteorTrace = new QTimer;
        QObject::connect( _tMeteorTrace, &QTimer::timeout, this, &meteorTraceWorker::addTrace );
    }
    else
        _tMeteorTrace->stop();
    double val = _ariseRng->generate();
    while( val <= 0.0 )
        val = _ariseRng->generate();
//    qDebug() << __PRETTY_FUNCTION__ << val;
    _tMeteorTrace->start( val );
}

void meteorTraceWorker::startTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    generateMeteorTraces();
    _isTracesRunning = true;
}

void meteorTraceWorker::stopTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    emit generationFinished();
    _isTracesRunning = false;
}

void meteorTraceWorker::addTrace() {
    double dtVal = _dtRng->generate();
    while( dtVal <= 0.0 )
        dtVal = _dtRng->generate();
    double pVal = _powerRng->generate();
    while( pVal <= 0.0 )
        pVal = _powerRng->generate();
    double elevationA = _elevRng->generate();
    double scatterA = _scatterRng->generate();

    QSharedPointer< meteorTraceChannel > mtc ( new meteorTraceChannel( _tMeteorTrace->interval(), dtVal, pVal, elevationA, scatterA ) );
    if ( !_tracesCounter.isNull() )
        (*_tracesCounter)++;
    emit traceGenerate( mtc );
    //_ariseMathExp << _existanceTimeMathExp << _existanceTimeSt << _aveAmpl;
    generateMeteorTraces();
}

void meteorTraceWorker::setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, double elevMin, double elevMax, double scatterMin, double scatterMax ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
    _elevMin = elevMin;
    _elevMax = elevMax;
    _scatterMin = scatterMin;
    _scatterMax = scatterMax;

    _ariseRng->clearParamValues();
    _ariseRng->addParamValue( _ariseMathExp );

    _dtRng->clearParamValues();
    _dtRng->addParamValue( _existanceTimeMathExp );
    _dtRng->addParamValue( _existanceTimeSt );

    _powerRng->clearParamValues();
    _powerRng->addParamValue( _aveAmpl );

    _elevRng->clearParamValues();
    _elevRng->addParamValue( _elevMin );
    _elevRng->addParamValue( _elevMax );

    _scatterRng->clearParamValues();
    _scatterRng->addParamValue( _scatterMin );
    _scatterRng->addParamValue( _scatterMax );
    qDebug() << __PRETTY_FUNCTION__ << QString("Random parameters were set");
}
