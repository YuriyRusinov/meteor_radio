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

meteorRadioController::meteorRadioController( const QVector< QSharedPointer< meteorRadioStation > >& mStations, QObject* parent )
    : QObject( parent ) {
    int nst = mStations.size();

    for ( int i = 0; i < nst; i++ ) {
        QThread* messageThread = new QThread;
        meteorRadioWorker* mRWorker = new meteorRadioWorker ( mStations[i] );
        mRWorker->moveToThread( messageThread );
        QObject::connect( messageThread, &QThread::finished, mRWorker, &QObject::deleteLater );
        QObject::connect( this, &meteorRadioController::operate, mRWorker, &meteorRadioWorker::generateMessages );
        QObject::connect( this, &meteorRadioController::finish, mRWorker, &meteorRadioWorker::stopGen );
        QObject::connect( this, &meteorRadioController::finish, messageThread, &QThread::quit );
        QObject::connect( mRWorker, &meteorRadioWorker::modellingFinished, this, &meteorRadioController::handleMessages );
        _messageThreads.append( messageThread );
        _mStationsW.append( mRWorker );
        messageThread->start();
    }

}

meteorRadioController::~meteorRadioController() {
    int n = _messageThreads.size();
    for ( int i=0; i<n; i++ ) {
        QThread* messageThread = _messageThreads[i];
        messageThread->quit();
        messageThread->wait();
        delete messageThread;
    }
    _messageThreads.clear();
}

void meteorRadioController::handleMessages() {
    qDebug() << __PRETTY_FUNCTION__ << tr("Test modelling was finished");
    int n = _messageThreads.size();
    for ( int i=0; i<n; i++ ) {
        QThread* messageThread = _messageThreads[i];
        messageThread->wait();
        messageThread->quit();
    }
    qDebug() << __PRETTY_FUNCTION__ << tr("Test threads were finished");
}

void meteorRadioController::startMess() {
    qDebug() << __PRETTY_FUNCTION__;
    emit operate();
}

void meteorRadioController::stopMess() {
    int n = _messageThreads.size();
    qDebug() << __PRETTY_FUNCTION__ << n;
    for ( int i=0; i<n; i++ ) {
        emit finish();
        QThread* messageThread = _messageThreads[i];
        qDebug() << __PRETTY_FUNCTION__ << i << messageThread->isRunning();
//        messageThread->terminate();
        qDebug() << __PRETTY_FUNCTION__ << messageThread->isRunning();
        messageThread->wait();
        qDebug() << __PRETTY_FUNCTION__ << messageThread->isRunning();
        messageThread->quit();
        qDebug() << __PRETTY_FUNCTION__ << messageThread->isRunning();
    }
}
