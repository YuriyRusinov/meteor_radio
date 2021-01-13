/*
 * @brief Загрузчик сущностей из БД
 * meteorLoader.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <pRecordC.h>
#include <pParamValue.h>
#include <meteorRadioStation.h>
#include "meteor_constants.h"
#include "meteorLoader.h"

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
        QSharedPointer< const pParamValue > pValueLon = precs.value()->paramValue("longitude");
        QSharedPointer< const pParamValue > pValueLat = precs.value()->paramValue("latitude");
        QSharedPointer< const pParamValue > pValueSrid = precs.value()->paramValue("srid");
        QSharedPointer< const pParamValue > pValueFreq = precs.value()->paramValue("frequency");
        QSharedPointer< const pParamValue > pValueRand = precs.value()->paramValue("id_message_gen");
        QSharedPointer< const pParamValue > pValueType = precs.value()->paramValue("station_type");

        QSharedPointer< meteorRadioStation > p_mrs ( new meteorRadioStation( pValueId->value().toLongLong(),
                                                                             pValueSN->value().toInt(),
                                                                             pValueLon->value().toDouble(),
                                                                             pValueLat->value().toDouble(),
                                                                             pValueSrid->value().toInt(),
                                                                             pValueFreq->value().toDouble(),
                                                                             pValueType->value().toInt()
                ) );
        res.append( p_mrs );
    }
    return res;
}
