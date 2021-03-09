/*
 * @brief Класс контроллер генерации тестовых сообщений для станций метеорной связи
 * meteorRadioController.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include "meteorRadioWorker.h"
#include "meteorRadioController.h"
#include <meteorTraceChannel.h>

meteorRadioController::meteorRadioController( const QVector< QSharedPointer< meteorRadioStation > >& mStations, QObject* parent )
    : QObject( parent ),
    _stationsThread( new QThread ) {
    int nst = mStations.size();

    for ( int i = 0; i < nst; i++ ) {
        meteorRadioWorker* mRWorker = new meteorRadioWorker ( mStations[i] );
        mRWorker->moveToThread( _stationsThread );
        QObject::connect( _stationsThread, &QThread::finished, mRWorker, &QObject::deleteLater );
        QObject::connect( this, &meteorRadioController::operate, mRWorker, &meteorRadioWorker::generateMessages );
        QObject::connect( this, &meteorRadioController::finish, mRWorker, &meteorRadioWorker::stopGen );
        QObject::connect( this, &meteorRadioController::finish, _stationsThread, &QThread::quit );
        QObject::connect( this, &meteorRadioController::sendTraceToStations, mRWorker, &meteorRadioWorker::clearMessagesToChannel, Qt::DirectConnection );
        QObject::connect( mRWorker, &meteorRadioWorker::modellingFinished, this, &meteorRadioController::handleMessages );
        _mStationsW.append( mRWorker );
    }
    _stationsThread->start();

}

meteorRadioController::~meteorRadioController() {
    _stationsThread->quit();
    _stationsThread->wait();
    delete _stationsThread;
}

void meteorRadioController::handleMessages() {
    qDebug() << __PRETTY_FUNCTION__ << tr("Test modelling was finished");
    _stationsThread->wait();
    _stationsThread->quit();
    qDebug() << __PRETTY_FUNCTION__ << tr("Test threads were finished");
}

void meteorRadioController::startMess() {
    qDebug() << __PRETTY_FUNCTION__;
    emit operate();
}

void meteorRadioController::stopMess() {
    emit finish();
    _stationsThread->wait();
    _stationsThread->quit();
}

void meteorRadioController::getMeteorTrace( QSharedPointer< meteorTraceChannel > mtc ) {
//    qDebug() << __PRETTY_FUNCTION__ << ( mtc.isNull() ? QString() : QString("Meteor trace was arrived") );
    emit sendTraceToStations( mtc );
}
