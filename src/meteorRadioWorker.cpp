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

#include "meteorRadioWorker.h"

meteorRadioWorker::meteorRadioWorker() : QObject() {}
meteorRadioWorker::~meteorRadioWorker() {}

void meteorRadioWorker::generateMessages() {
    QFile testMessFile ("message_test.dat");
    if (!testMessFile.open(QIODevice::WriteOnly))
        return;
    QDataStream messStream( &testMessFile );
    for ( int i=0; i<10000; i++ ) {
        messStream << QString("test message %1").arg ( i ) << "\n";// << std::endl;
    }
}
