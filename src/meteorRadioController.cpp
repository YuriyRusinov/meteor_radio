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

meteorRadioController::meteorRadioController() {
    meteorRadioWorker* mRWorker = new meteorRadioWorker;
    mRWorker->moveToThread( &messThread );
    QObject::connect( &messThread, &QThread::finished, mRWorker, &QObject::deleteLater );
    QObject::connect( this, &meteorRadioController::operate, mRWorker, &meteorRadioWorker::generateMessages );
    QObject::connect( mRWorker, &meteorRadioWorker::modellingFinished, this, &meteorRadioController::handleMessages );
    messThread.start();
}

meteorRadioController::~meteorRadioController() {
    messThread.quit();
    messThread.wait();
}

void meteorRadioController::handleMessages() {
    qDebug() << __PRETTY_FUNCTION__ << tr("Test modelling was finished");
}

void meteorRadioController::startMess() {
    emit operate();
}
