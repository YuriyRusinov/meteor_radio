/*
 * @brief Класс генерации метеорных следов для станций метеорной связи
 * meteorTraceWorker.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <memory>

#include <gaussianRandomNumbGenerator.h>
#include <randomNumbGenerator.h>
#include "meteorTraceChannel.h"
#include "meteorTraceWorker.h"

meteorTraceWorker::meteorTraceWorker( QObject* parent )
    : QObject( parent ) {
    qDebug() << __PRETTY_FUNCTION__;
}

meteorTraceWorker::~meteorTraceWorker() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorTraceWorker::generateMeteorTraces() {
    qDebug() << __PRETTY_FUNCTION__;
    shared_ptr< randomNumbersGenerator > rng ( new gaussianRandomNumbersGenerator );
}

void meteorTraceWorker::startTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorTraceWorker::stopTraceGen() {
    qDebug() << __PRETTY_FUNCTION__;
    emit generationFinished();
}
