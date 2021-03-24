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
using std::weak_ptr;

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
    while( val <= 0.0 )
        val = rng->generate();
    QThread* cThr = QThread::currentThread();
    if ( !_tMessage ) {
        _tMessage = new QTimer;
        QObject::connect( _tMessage, &QTimer::timeout, this, &meteorRadioWorker::addMessage );
    }
    _tMessage->start( 1000/val );
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
    queue< shared_ptr<message> > messq = _meteorRadioStaion->getMessages();
    int nMessages = _meteorRadioStaion->messageSize();
    if( messq.empty() || nMessages == 0 )
        return;
    qDebug() << __PRETTY_FUNCTION__ << nMessages;
    int nMessLength = 0;
    qDebug() << __PRETTY_FUNCTION__ << QString("Messages queue was got, number is %1").arg( nMessages );
    for(int i=0; i<nMessages; i++) {
        qDebug() << __PRETTY_FUNCTION__ << QString("Message cycle started");
        shared_ptr<message> pMess = messq.front();
        qDebug() << __PRETTY_FUNCTION__ << QString("        front");
        if( pMess == nullptr || weak_ptr<message>(pMess).expired() ) {
            qDebug() << __PRETTY_FUNCTION__ << QString("Null message");
            nMessLength++;
        }
        else {
            qDebug() << __PRETTY_FUNCTION__ << QString("message length") << (pMess == nullptr );
            string addr = pMess->getAddress();
            qDebug() << __PRETTY_FUNCTION__ << QString("    address");
            string mess = pMess->getMess();
            qDebug() << __PRETTY_FUNCTION__ << QString("    message");
            nMessLength += addr.length() + mess.length();
            qDebug() << __PRETTY_FUNCTION__ << QString("message length calculated");
        }
        qDebug() << __PRETTY_FUNCTION__ << QString("Message length was calculated");
        messq.pop();
        qDebug() << __PRETTY_FUNCTION__ << QString("Message was popped, length is %1").arg( nMessLength );
    }
    qDebug() << __PRETTY_FUNCTION__ << QString("Messages were read");
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
