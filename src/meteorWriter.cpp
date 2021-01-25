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
    qint64 idRand = -1;
    if( mrs->getMessagesGen() != nullptr ) {
        shared_ptr< randomNumbersGenerator > rng ( mrs->getMessagesGen() );
        idRand = insertRandomGenerator( rng );
    }
    QString sql_query = QString("select insertMeteorRadioStation( %1, %2, %3::smallint, %4, %5, %6, %7, %8 );")
        .arg( mrs->getStationNumber() )
        .arg( mrs->getAddress().isEmpty() ? QString("NULL::varchar") : QString("'%1'::varchar").arg(mrs->getAddress()) )
        .arg( mrs->getType() )
        .arg( mrs->getLongitude() )
        .arg( mrs->getLatitude() )
        .arg( mrs->getSrid() )
        .arg( mrs->getFrequency() )
        .arg( idRand < 0 ? QString("NULL") : QString::number( idRand  ));
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
    qint64 idRand = -1;
    if( mrs->getMessagesGen() ) {
        if( mrs->getMessagesGen()->getId() < 0 )
            idRand = insertRandomGenerator( mrs->getMessagesGen() );
        else
            idRand = updateRandomGenerator( mrs->getMessagesGen() );
    }
    QString sql_query = QString("select updateMeteorRadioStation( %1, %2, %3::varchar, %4::smallint, %5, %6, %7, %8, %9);")
        .arg( mrs->getId() )
        .arg( mrs->getStationNumber() )
        .arg( mrs->getAddress().isEmpty() ? QString("NULL::varchar") : QString("'%1'").arg(mrs->getAddress()) )
        .arg( mrs->getType() )
        .arg( mrs->getLongitude() )
        .arg( mrs->getLatitude() )
        .arg( mrs->getSrid() )
        .arg( mrs->getFrequency() )
        .arg( idRand < 0 ? QString("NULL") : QString::number( idRand ));
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

qint64 meteorWriter::deleteStation( QSharedPointer< meteorRadioStation > mrs ) const {
    if( mrs.isNull() )
        return -1;
    //if( mrs->getMessagesGen() )
    //    quint64 idRand = deleteRandomGenerator( QSharedPointer< randomNumbersGenerator >( mrs->getMessagesGen().get() ) );
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

qint64 meteorWriter::insertRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const {
    qDebug() << __PRETTY_FUNCTION__;
    if( rng == nullptr )
        return -1;

    int npMin = 0;
    switch( rng->getDistrib() ) {
        case DistributionFunc::_Undefined: default: return -2; break;
        case DistributionFunc::_Uniform: case DistributionFunc::_Gaussian: npMin = 2; break;
        case DistributionFunc::_Exponential: case DistributionFunc::_Rayleigh: npMin = 1; break;
    }
    if( rng->getParamSize() < npMin )
        return -2;
    QString sql_query = QString("select insertRandomParams(%1, %2, %3)")
                            .arg( rng->getDistrib() )
                            .arg( rng->at(0) )
                            .arg( npMin == 1 ? QString("null::float8") : QString::number( rng->at(1) ));
    qDebug() << __PRETTY_FUNCTION__ << sql_query;

    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idRng = gpr->getCellAsInt( 0, 0 );
    rng->setId( idRng );
    delete gpr;
    return idRng;
}

qint64 meteorWriter::updateRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const {
    if( rng == nullptr )
        return -1;

    int npMin = 0;
    switch( rng->getDistrib() ) {
        case DistributionFunc::_Undefined: default: return -2; break;
        case DistributionFunc::_Uniform: case DistributionFunc::_Gaussian: npMin = 2; break;
        case DistributionFunc::_Exponential: case DistributionFunc::_Rayleigh: npMin = 1; break;
    }
    if( rng->getParamSize() < npMin )
        return -2;
    QString sql_query = QString("select updateRandomParams(%1, %2, %3, %4)")
                            .arg( rng->getId() )
                            .arg( rng->getDistrib() )
                            .arg( rng->at(0) )
                            .arg( npMin == 1 ? QString("null::float8") : QString::number( rng->at(1) ));

    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idRng = gpr->getCellAsInt( 0, 0 );
    rng->setId( idRng );
    delete gpr;
    return idRng;
}

qint64 meteorWriter::deleteRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const {
    if( rng == nullptr )
        return -1;

    QString sql_query = QString("select deleteRandomParams( %1 )").arg ( rng->getId() );
    GISPatrolDatabase * db = getDb();
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idRng = gpr->getCellAsInt( 0, 0 );
    rng->setId( idRng );
    delete gpr;
    return idRng;
}
