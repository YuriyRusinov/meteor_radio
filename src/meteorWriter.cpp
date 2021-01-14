/*
 * @brief Класс, управляющий записью сущностей в БД.
 * meteorWriter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorRadioSingleton.h"
#include "meteorWriter.h"

meteorWriter::meteorWriter( GISPatrolDatabase* db, QObject* parent )
    : pDBWriter( db, parent ) {
}

meteorWriter::~meteorWriter() {
}

qint64 meteorWriter::insertStation( QSharedPointer< meteorRadioStation > mrs ) const {
}

qint64 meteorWriter::updateStation( QSharedPointer< meteorRadioStation > mrs ) const {
}

qint64 meteorWriter::deleteStation( QSharedPointer< meteorRadioStation > mrs ) const {

}
