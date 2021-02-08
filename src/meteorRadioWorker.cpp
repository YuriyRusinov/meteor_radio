/*
 * @brief Класс генерации тестовых сообщений для станций метеорной связи
 * meteorRadioWorker.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QFile>
#include <QDataStream>
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
    _meteorRadioStaion( meteorRadioStaion ) {
}

meteorRadioWorker::~meteorRadioWorker() {}

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
//    QTimer * tMess = new QTimer;
}
