/*
 * @brief Класс генерации тестовых сообщений для станций метеорной связи
 * meteorRadioWorker.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QBuffer>
#include <QFile>
#include <QDataStream>
#include <QDateTime>
#include <QIODevice>
#include <QThread>
#include <QTimer>
#include <QtDebug>
#include <memory>

#include "meteorRadioStation.h"
#include "meteorRadioWorker.h"
#include <randomNumbGenerator.h>
#include "message.h"
#include <meteorTraceChannel.h>

using std::shared_ptr;

meteorRadioWorker::meteorRadioWorker( QSharedPointer< meteorRadioStation > meteorRadioStaion )
    : QObject(),
    _meteorRadioStaion( meteorRadioStaion ),
    _tMessage( nullptr ),
    _isRadioRunning( false ),
    _tChannel( nullptr ) {
}

meteorRadioWorker::~meteorRadioWorker() {
    delete _tMessage;
    delete _tChannel;
}

void meteorRadioWorker::generateMessages() {
    if( _meteorRadioStaion.isNull() )
        return;
    _isRadioRunning = true;
    shared_ptr< randomNumbersGenerator > rng = _meteorRadioStaion->getMessagesGen();
    double val = rng->generate();
    QThread* cThr = QThread::currentThread();
    if ( !_tMessage ) {
        _tMessage = new QTimer;
        QObject::connect( _tMessage, &QTimer::timeout, this, &meteorRadioWorker::addMessage );
    }
    _tMessage->start( 1000*val );
}

void meteorRadioWorker::addMessage() {
    QByteArray tByteArr;
    QBuffer messDev( &tByteArr );
    messDev.open( QIODevice::WriteOnly );
    QDataStream messStream( &messDev );
    messStream << QString("test message from station %1").arg( _meteorRadioStaion->getId() );
    _tMessage->stop();
    QThread* cThr = QThread::currentThread();
    if( _meteorRadioStaion->addrSize() < 1 ) {
        if( _isRadioRunning && cThr && cThr->isRunning() )
            generateMessages();
        return;
    }
    std::string sAddr = _meteorRadioStaion->getAddress(0);
    shared_ptr< message > pMess( new message( sAddr, tByteArr.toStdString()) );
    _meteorRadioStaion->pushMessage( pMess );
//    qDebug() << __PRETTY_FUNCTION__ << _meteorRadioStaion->getId() << _meteorRadioStaion->messageSize();
    if( _isRadioRunning && cThr && cThr->isRunning() )
        generateMessages();
}

void meteorRadioWorker::stopGen() {
    qDebug() << __PRETTY_FUNCTION__;
    _isRadioRunning = false;
    emit modellingFinished();
}

void meteorRadioWorker::clearMessagesToChannel( QSharedPointer< meteorTraceChannel > mtc ) {
    if( !_tChannel ) {
        _tChannel = new QTimer;
        QObject::connect( _tChannel, &QTimer::timeout, this, &meteorRadioWorker::clearMess, Qt::DirectConnection );
    }
    else if( _tChannel->isActive() )
        return;
    double tStart = mtc->getAriseTime();
    qDebug() << __PRETTY_FUNCTION__ << ( mtc.isNull() ? QString() : QString("channel to station %1 was arrived").arg(_meteorRadioStaion->getId()) ) << tStart;
    _tChannel->start( tStart );
}

void meteorRadioWorker::clearMess() {
    qDebug() << __PRETTY_FUNCTION__;
    _tChannel->stop();
}
