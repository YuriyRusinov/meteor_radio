/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>

#include <meteorTraceChannel.h>
#include "meteorTraceGenerationFactory.h"
#include "meteorTraceController.h"
#include "meteorRadioStationsFactory.h"

QSharedPointer< meteorTraceChannel > meteorTraceGenerationFactory::generate() const {
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ),
    _mRSF( nullptr ),
    _mTraceController( new meteorTraceController ) {
    _mTraceController->startGenerate();
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {
    qDebug() << __PRETTY_FUNCTION__;
    _mTraceController->stopGenerate();
    delete _mTraceController;//->deleteLater();
}

void meteorTraceGenerationFactory::setStationFactory( meteorRadioStationsFactory* rsf ) {
    _mRSF =  rsf;
    QObject::connect( _mRSF, &meteorRadioStationsFactory::signalModStop, this, &meteorTraceGenerationFactory::stopTraceGen );
}

void meteorTraceGenerationFactory::stopTraceGen() {
    _mTraceController->stopGenerate();
}
