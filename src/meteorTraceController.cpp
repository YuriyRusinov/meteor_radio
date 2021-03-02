/*
 * @brief Класс контроллер потока генерации следов метеоров
 * meteorTraceController.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <QThread>
#include "meteorTraceWorker.h"
#include "meteorTraceController.h"
#include <meteorTraceChannel.h>

meteorTraceController::meteorTraceController( QObject* parent )
    : QObject( parent ),
    _mTraceW( new meteorTraceWorker ),
    _mTraceThread( new QThread ) {
    _mTraceW->moveToThread( _mTraceThread );

    traceInit();
}

meteorTraceController::~meteorTraceController() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceThread->quit();
    _mTraceThread->wait();
    delete _mTraceThread;//->deleteLater();
}

void meteorTraceController::startGenerate() {
    qDebug() << __PRETTY_FUNCTION__;
    if( !_mTraceThread->isRunning() || !_mTraceW ) {
        traceInit();
    }
    _mTraceW->setTraceGenParameters( _ariseMathExp, _existanceTimeMathExp, _existanceTimeSt, _aveAmpl );

    emit traceStart();
}

void meteorTraceController::stopGenerate() {
    qDebug() << __PRETTY_FUNCTION__;
    emit traceEnd();
    _mTraceThread->wait();
    _mTraceThread->quit();
}

void meteorTraceController::handleTraces() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceThread->wait();
    _mTraceThread->quit();
}

void meteorTraceController::traceInit() {
    _mTraceW = new meteorTraceWorker;
    _mTraceW->moveToThread( _mTraceThread );
    QObject::connect( _mTraceThread, &QThread::finished, _mTraceW, &QObject::deleteLater );
    QObject::connect( this, &meteorTraceController::traceStart, _mTraceW, &meteorTraceWorker::generateMeteorTraces );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceW, &meteorTraceWorker::stopTraceGen );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceThread, &QThread::quit );
    QObject::connect( _mTraceW, &meteorTraceWorker::generationFinished, this, &meteorTraceController::handleTraces );
    QObject::connect( _mTraceW, &meteorTraceWorker::traceGenerate, this, &meteorTraceController::procTraceChannel, Qt::DirectConnection );
    _mTraceThread->start();
}

void meteorTraceController::setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
}

void meteorTraceController::procTraceChannel( QSharedPointer< meteorTraceChannel > mtc ) {
    qDebug() << __PRETTY_FUNCTION__ << mtc.isNull();
}
