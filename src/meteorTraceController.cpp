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

meteorTraceController::meteorTraceController( QObject* parent )
    : QObject( parent ),
    _mTraceW( new meteorTraceWorker ),
    _mTraceThread( new QThread ) {
    _mTraceW->moveToThread( _mTraceThread );
    QObject::connect( _mTraceThread,  &QThread::finished, _mTraceW, &QObject::deleteLater );
    QObject::connect( this, &meteorTraceController::traceStart, _mTraceW, &meteorTraceWorker::startTraceGen );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceW, &meteorTraceWorker::stopTraceGen );
    QObject::connect( this, &meteorTraceController::traceEnd, _mTraceThread, &QThread::quit );
    QObject::connect( _mTraceW, &meteorTraceWorker::generationFinished, this, &meteorTraceController::handleTraces );
    _mTraceThread->start();
}

meteorTraceController::~meteorTraceController() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceThread->quit();
    _mTraceThread->wait();
//    _mTraceW->deleteLater();
    _mTraceThread->deleteLater();
}

void meteorTraceController::startGenerate() {
    qDebug() << __PRETTY_FUNCTION__;
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
