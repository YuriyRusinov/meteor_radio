/*
 * @brief Синглтон работы ПО моделирования метеорной радиосвязи
 * meteor_radio_singleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <gis_patroldatabase.h>
#include <gis_patrolpgdatabase.h>
#include <patrolsingleton.h>
#include <meteorLoader.h>
#include <meteorWriter.h>
#include "meteorRadioSingleton.h"
#include "meteorRadioStationsFactory.h"
#include "meteorTraceGenerationFactory.h"

meteorRadioSingleton* meteorRadioSingleton::_instance = nullptr;
PatrolSingleton* meteorRadioSingleton::_patrolInstance = nullptr;

meteorRadioSingleton* meteorRadioSingleton::getMeteorRadioS( QObject* parent ) {
    if( !_instance ) {
        _patrolInstance = PatrolSingleton::getPatrolS( parent );
        _instance = new meteorRadioSingleton( parent );
    }

    return _instance;
}

void meteorRadioSingleton::resetMRS() {
    if( _instance )
        delete _instance;
    PatrolSingleton::resetPatrol();
}

PatrolSingleton* meteorRadioSingleton::getPatrol() {
    return _patrolInstance;
}

meteorRadioSingleton::meteorRadioSingleton( QObject* parent ) : 
    QObject( parent ),
    _mDb( _patrolInstance->getDb() ),//new GISPatrolPGDatabase ),
    _mLoader( new meteorLoader( _mDb ) ),
    _mWriter( new meteorWriter( _mDb ) ),
    _mrsF( new meteorRadioStationsFactory( _mLoader, _mWriter, parent ) ),
    _mTrGF ( new meteorTraceGenerationFactory ) {
    if (_instance) {
        qFatal("There should be only one MeteorRadioSingleton object");
    }
    _instance = this;
    _mTrGF->setStationFactory( _mrsF );
    _mrsF->setTraceGenerationFactory( _mTrGF );
    qDebug() << __PRETTY_FUNCTION__;
}

meteorRadioSingleton::~meteorRadioSingleton() {
    _instance = nullptr;
    delete _mTrGF;
    delete _mrsF;
    qDebug() << __PRETTY_FUNCTION__;
}
