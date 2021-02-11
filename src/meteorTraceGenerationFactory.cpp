/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <meteorTraceChannel.h>
#include "meteorTraceGenerationFactory.h"

QSharedPointer< meteorTraceChannel > meteorTraceGenerationFactory::generate() const {
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ) {
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {}
