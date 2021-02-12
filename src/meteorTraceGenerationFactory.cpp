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
#include "meteorRadioStationsFactory.h"

QSharedPointer< meteorTraceChannel > meteorTraceGenerationFactory::generate() const {
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ), _mRSF( nullptr ) {
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorTraceGenerationFactory::setStationFactory( meteorRadioStationsFactory* rsf ) {
    _mRSF =  rsf;
}
