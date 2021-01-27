/*
 * @brief Загрузчик сущностей из БД
 * meteorLoader.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <gis_patroldatabase.h>
#include <pRecordC.h>
#include <pParamValue.h>
#include <meteorRadioStation.h>
#include <randomNumbGenerator.h>
#include <uniRandomNumbGenerator.h>
#include <expRandomNumbGenerator.h>
#include <gaussianRandomNumbGenerator.h>
#include <rayleighRandomNumbGenerator.h>
#include "meteor_constants.h"
#include "meteorLoader.h"

using std::make_shared;
meteorLoader::meteorLoader( GISPatrolDatabase* db, QObject* parent )
    : pDBLoader( db, parent ) {
}

meteorLoader::~meteorLoader() {
}

QVector< QSharedPointer< meteorRadioStation > > meteorLoader::loadStations() const {
    if( getDb() == nullptr )
        return QVector< QSharedPointer< meteorRadioStation > >();

    QSharedPointer< pIObject > pMeteorIO = loadIO( IO_ID_METEOR_RADIO_STATION );
    QMap< qint64, QSharedPointer< pRecordCopy > > pMeteorRadioRecs = loadRecords( pMeteorIO );
    QVector< QSharedPointer< meteorRadioStation > > res;
    for( QMap< qint64, QSharedPointer< pRecordCopy > >::const_iterator precs = pMeteorRadioRecs.constBegin();
            precs != pMeteorRadioRecs.constEnd();
            precs++) {
        QSharedPointer< const pParamValue > pValueId = precs.value()->paramValue("id");
        QSharedPointer< const pParamValue > pValueSN = precs.value()->paramValue("station_number");
        QSharedPointer< const pParamValue > pValueSAddr = precs.value()->paramValue("station_address");
        QSharedPointer< const pParamValue > pValueLon = precs.value()->paramValue("longitude");
        QSharedPointer< const pParamValue > pValueLat = precs.value()->paramValue("latitude");
        QSharedPointer< const pParamValue > pValueSrid = precs.value()->paramValue("srid");
        QSharedPointer< const pParamValue > pValueFreq = precs.value()->paramValue("frequency");
        QSharedPointer< const pParamValue > pValueRand = precs.value()->paramValue("id_message_gen");
        QSharedPointer< const pParamValue > pValueType = precs.value()->paramValue("station_type");

        QSharedPointer< meteorRadioStation > p_mrs ( new meteorRadioStation( pValueId->value().toLongLong(),
                                                                             pValueSN->value().toInt(),
                                                                             pValueSAddr->value().toString(),
                                                                             pValueLon->value().toDouble(),
                                                                             pValueLat->value().toDouble(),
                                                                             pValueSrid->value().toInt(),
                                                                             pValueFreq->value().toDouble(),
                                                                             pValueType->value().toInt()
                ) );
        shared_ptr< randomNumbersGenerator > rng = loadStatRandomGen( pValueRand->value().toInt() );
        qDebug() << __PRETTY_FUNCTION__ << (rng == nullptr ? QString("Null random generator") : QString::number(rng->getId()));
        p_mrs->setMessagesGen( rng );
        res.append( p_mrs );
    }
    return res;
}

shared_ptr< randomNumbersGenerator > meteorLoader::loadStatRandomGen( qint32 idRandGen ) const {
    if( getDb() == nullptr )
        return nullptr;

    GISPatrolDatabase* db = getDb();
    QString sql_query = QString("select * from getRandomGen( %1 );").arg( idRandGen );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolResult * gpr = db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;
    }
    shared_ptr< randomNumbersGenerator > rng( nullptr );
    DistributionFunc idDistrib = (DistributionFunc)gpr->getCellAsInt(0, 2);
    switch( idDistrib ) {
        case _Undefined: default: return nullptr; break;
        case _Uniform: rng = shared_ptr< randomNumbersGenerator >( new uniRandomNumbersGenerator( idRandGen ) ); break;
        case _Exponential: rng = shared_ptr< randomNumbersGenerator >( new expRandomNumbersGenerator( idRandGen ) ); break;
        case _Gaussian: rng = shared_ptr< randomNumbersGenerator >( new gaussianRandomNumbersGenerator( idRandGen ) ); break;
        case _Rayleigh: rng = shared_ptr< randomNumbersGenerator >( new rayleighRandomNumbersGenerator(idRandGen) ); break;
    }
    QStringList vParamList = gpr->getCell(0, 3).toStringList();
    int np = vParamList.size();
    for( int i=0; i<np; i++ ) {
        bool ok;
        double val = vParamList[i].toDouble( &ok );
        if( ok )
            rng->addParamValue( val );
    }
    delete gpr;

    return rng;
}
