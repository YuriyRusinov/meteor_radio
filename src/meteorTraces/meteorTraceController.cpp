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

meteorTraceController::meteorTraceController( QSharedPointer< int > traceCounter, QObject* parent )
    : QObject( parent ),
    _tracesCounter( traceCounter ),
    _mTraceW( new meteorTraceWorker( traceCounter ) ),
    _mTraceThread( new QThread ) {
    _mTraceW->moveToThread( _mTraceThread );

    traceInit();
}

meteorTraceController::~meteorTraceController() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceThread->quit();
    _mTraceThread->wait();
//    if( _mTraceW )
//        _mTraceW->deleteLater();

//    _mTraceThread->deleteLater();
}

void meteorTraceController::startGenerate() {
    qDebug() << __PRETTY_FUNCTION__;
    if( !_mTraceThread->isRunning() || !_mTraceW ) {
        traceInit();
    }
    _mTraceW->setTraceGenParameters( _ariseMathExp, _existanceTimeMathExp, _existanceTimeSt, _aveAmpl );
    qDebug() << __PRETTY_FUNCTION__ << "Parameters were set";

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
    qDebug() << __PRETTY_FUNCTION__;
    if( !_mTraceW ) {
        _mTraceW = new meteorTraceWorker;
        _mTraceW->moveToThread( _mTraceThread );
    }
    QObject::connect( _mTraceThread, &QThread::finished, _mTraceW, &QObject::deleteLater );
    QObject::connect( _mTraceW, &QObject::destroyed, this, &meteorTraceController::workerDestroyed );
    qDebug() << __PRETTY_FUNCTION__ << "thread removing was connected";
//    _mTraceThread->start();
    QObject::connect( this, &meteorTraceController::traceStart, _mTraceW, &meteorTraceWorker::generateMeteorTraces );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceW, &meteorTraceWorker::stopTraceGen );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceThread, &QThread::quit );
    QObject::connect( _mTraceW, &meteorTraceWorker::generationFinished, this, &meteorTraceController::handleTraces );
    QObject::connect( _mTraceW, &meteorTraceWorker::traceGenerate, this, &meteorTraceController::procTraceChannel, Qt::DirectConnection );
    qDebug() << __PRETTY_FUNCTION__ << "All objects were connected";
    _mTraceThread->start();
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorTraceController::setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
}

void meteorTraceController::procTraceChannel( QSharedPointer< meteorTraceChannel > mtc ) {
    if( mtc.isNull() )
        return;
    //qDebug() << __PRETTY_FUNCTION__;
    emit sendTraceChannel( mtc );
}

void meteorTraceController::workerDestroyed() {
    _mTraceW = nullptr;
}
