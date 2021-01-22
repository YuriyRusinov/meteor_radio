/*
 * @brief Класс, управляющий записью сущностей в БД.
 * meteorWriter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <gis_patrolresult.h>
#include <gis_patroldatabase.h>
#include <meteorRadioStation.h>
#include <randomNumbGenerator.h>
#include "meteorRadioSingleton.h"
#include "meteorWriter.h"

meteorWriter::meteorWriter( GISPatrolDatabase* db, QObject* parent )
    : pDBWriter( db, parent ) {
}

meteorWriter::~meteorWriter() {
}

qint64 meteorWriter::insertStation( QSharedPointer< meteorRadioStation > mrs ) const {
    if( mrs.isNull() )
        return -1;
    QString sql_query = QString("select insertMeteorRadioStation( %1, %2, %3::smallint, %4, %5, %6, %7, %8 );")
        .arg( mrs->getStationNumber() )
        .arg( mrs->getAddress().isEmpty() ? QString("NULL::varchar") : QString("'%1'::varchar").arg(mrs->getAddress()) )
        .arg( mrs->getType() )
        .arg( mrs->getLongitude() )
        .arg( mrs->getLatitude() )
        .arg( mrs->getSrid() )
        .arg( mrs->getFrequency() )
        .arg( mrs->getMessagesGen() ? QString("NULL") : QString::number( mrs->getMessagesGen()->getId()) );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idMRS = gpr->getCellAsInt( 0, 0 );
    mrs->setId( idMRS );
    delete gpr;
    return idMRS;
}

qint64 meteorWriter::updateStation( QSharedPointer< meteorRadioStation > mrs ) const {
    if( mrs.isNull() )
        return -1;
    QString sql_query = QString("select updateMeteorRadioStation( %1, %2, %3, %4, %5, %6, %7, %8, %9);")
        .arg( mrs->getId() )
        .arg( mrs->getStationNumber() )
        .arg( mrs->getAddress().isEmpty() ? QString("NULL::varchar") : QString("'%1'").arg(mrs->getAddress()) )
        .arg( mrs->getType() )
        .arg( mrs->getLongitude() )
        .arg( mrs->getLatitude() )
        .arg( mrs->getSrid() )
        .arg( mrs->getFrequency() )
        .arg( mrs->getMessagesGen() ? QString("NULL") : QString::number( mrs->getMessagesGen()->getId()) );
    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idMRS = gpr->getCellAsInt( 0, 0 );
    mrs->setId( idMRS );
    delete gpr;
    return idMRS;
}

qint64 meteorWriter::deleteStation( QSharedPointer< meteorRadioStation > mrs ) const {
    if( mrs.isNull() )
        return -1;
    QString sql_query = QString("select delMeteorRadioStation( %1 );")
        .arg( mrs->getId() );
    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idMRS = gpr->getCellAsInt( 0, 0 );
    mrs->setId( idMRS );
    delete gpr;
    return idMRS;
}

qint64 meteorWriter::insertRandomGenerator( QSharedPointer< randomNumbersGenerator > rng ) const {
}

qint64 meteorWriter::updateRandomGenerator( QSharedPointer< randomNumbersGenerator > rng ) const {
}

qint64 meteorWriter::deleteRandomGenerator( QSharedPointer< randomNumbersGenerator > rng ) const {

}
