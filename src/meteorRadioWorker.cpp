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
#include <QIODevice>
#include <QThread>
#include <QTimer>
#include <QtDebug>
#include <memory>

#include "meteorRadioStation.h"
#include "meteorRadioWorker.h"
#include <randomNumbGenerator.h>

using std::shared_ptr;

meteorRadioWorker::meteorRadioWorker( QSharedPointer< meteorRadioStation > meteorRadioStaion )
    : QObject(),
    _meteorRadioStaion( meteorRadioStaion ),
    _tMessage( nullptr ) {
}

meteorRadioWorker::~meteorRadioWorker() {
    delete _tMessage;
}

void meteorRadioWorker::generateMessages() {
    if( _meteorRadioStaion.isNull() )
        return;
/*    QFile testMessFile ("message_test.dat");
    if (!testMessFile.open(QIODevice::WriteOnly))
        return;
    QDataStream messStream( &testMessFile );
    for ( int i=0; i<10000; i++ ) {
        messStream << QString("test message %1").arg ( i ) << "\n";// << std::endl;
    }
*/
    shared_ptr< randomNumbersGenerator > rng = _meteorRadioStaion->getMessagesGen();
    double val = rng->generate();
    QThread* cThr = QThread::currentThread();
    qDebug() << __PRETTY_FUNCTION__ << _meteorRadioStaion->getId() << QThread::currentThreadId() << val;
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
    if( cThr && cThr->isRunning() )
        generateMessages();
}

void meteorRadioWorker::stopGen() {
//    QThread* cThr = QThread::currentThread();
//    if( cThr && cThr->isRunning() )
//        cThr->wait();
    emit modellingFinished();
}
