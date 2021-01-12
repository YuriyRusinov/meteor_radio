/*
 * @brief Загрузчик сущностей из БД
 * meteorLoader.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorLoader.h"

meteorLoader::meteorLoader( GISPatrolDatabase* db, QObject* parent )
    : pDBLoader( db, parent ) {
}

meteorLoader::~meteorLoader() {
}

QVector< QSharedPointer< meteorRadioStation > > meteorLoader::loadStations() const {
    return QVector< QSharedPointer< meteorRadioStation > >();
}
