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
#include <memory>

#include <gaussianRandomNumbGenerator.h>
#include <randomNumbGenerator.h>
#include "meteorTraceChannel.h"
#include "meteorTraceWorker.h"

meteorTraceWorker::meteorTraceWorker( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, QObject* parent )
    : QObject( parent ),
    _tMeteorTrace( nullptr ),
    _isTracesRunning( false ),
    _ariseMathExp( ariseM ),
    _existanceTimeMathExp( existanceTime ),
    _existanceTimeSt( existanceTimeSt ),
    _aveAmpl( aveAmpl ) {
    qDebug() << __PRETTY_FUNCTION__;
}

meteorTraceWorker::~meteorTraceWorker() {
    qDebug() << __PRETTY_FUNCTION__;
    delete _tMeteorTrace;
}

void meteorTraceWorker::generateMeteorTraces() {
    qDebug() << __PRETTY_FUNCTION__;
    shared_ptr< randomNumbersGenerator > rng ( new gaussianRandomNumbersGenerator );
    if( !_tMeteorTrace ) {
        _tMeteorTrace = new QTimer;
        QObject::connect( _tMeteorTrace, &QTimer::timeout, this, &meteorTraceWorker::addTrace );
    }
    _tMeteorTrace->start( 1000.0 );
}

void meteorTraceWorker::startTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    generateMeteorTraces();
}

void meteorTraceWorker::stopTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    emit generationFinished();
}

void meteorTraceWorker::addTrace() {
    qDebug() << __PRETTY_FUNCTION__ << _ariseMathExp << _existanceTimeMathExp << _existanceTimeSt << _aveAmpl;
}

void meteorTraceWorker::setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
}
