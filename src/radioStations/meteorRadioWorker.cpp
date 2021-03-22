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

meteorRadioWorker::meteorRadioWorker( double messageSpeed, QSharedPointer< meteorRadioStation > meteorRadioStaion, QSharedPointer< int > messCounter, QSharedPointer< int > allCounter, QObject* parent )
    : QObject( parent ),
    _meteorRadioStaion( meteorRadioStaion ),
    _tMessage( nullptr ),
    _tChannel( nullptr ),
    _isRadioRunning( false ),
    _messageSpeed( messageSpeed ),
    _dtMess( -1.0 ),
    _messagesCounter( messCounter ),
    _allBytesCounter( allCounter ) {
        qDebug() << __PRETTY_FUNCTION__ << !_messagesCounter.isNull() << !_allBytesCounter.isNull();
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
    _dtMess = mtc->getTimeTrace();
    //qDebug() << __PRETTY_FUNCTION__ << ( mtc.isNull() ? QString() : QString("channel to station %1 was arrived").arg(_meteorRadioStaion->getId()) ) << tStart;
    _tChannel->start( tStart );
}

void meteorRadioWorker::clearMess() {
    _tChannel->stop();
    int nMessages = _meteorRadioStaion->messageSize();
    if( nMessages == 0 )
        return;
    qDebug() << __PRETTY_FUNCTION__ << nMessages;
    int nMessLength = 0;
    queue< shared_ptr<message> > messq = _meteorRadioStaion->getMessages();
    for(int i=0; i<nMessages; i++) {
        shared_ptr<message> pMess = messq.front();
        if( pMess == nullptr )
            nMessLength++;
        else
            nMessLength += pMess->getAddress().length() + pMess->getMess().length();
        messq.pop();
    }
    if( nMessLength == 0 ) {
        _meteorRadioStaion->clearMessages();
        emit sendMessagesNumb( nMessages, nMessLength+1 );
        return;
    }
    int nMessMax = (int) (_dtMess*_messageSpeed)/nMessLength;
    if( nMessages <= nMessMax ) {
        emit sendMessagesNumb( nMessages, nMessLength );
        if( !_messagesCounter.isNull() ) {
            _stationMutex.lock();
            *_messagesCounter += nMessages;
            *_allBytesCounter += nMessLength;
            _stationMutex.unlock();
        }
        _meteorRadioStaion->clearMessages();
    }
    else {
//        queue< shared_ptr<message> > messq = _meteorRadioStaion->getMessages();
        for(int i=0; i<nMessages-nMessMax; i++)
            _meteorRadioStaion->popMessage();
        if( !_messagesCounter.isNull() ) {
            _stationMutex.lock();
            *_messagesCounter += nMessages-nMessMax;
            *_allBytesCounter += nMessLength;
            _stationMutex.unlock();
        }
        emit sendMessagesNumb( nMessages-nMessMax, nMessLength );
    }
//    qDebug() << __PRETTY_FUNCTION__ << nMessages << nMessMax << nMessLength << ( _messagesCounter.isNull() ? -1 : *_messagesCounter ) << ( _allBytesCounter.isNull() ? -1 : *_allBytesCounter );
}
