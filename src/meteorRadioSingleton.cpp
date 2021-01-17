/*
 * @brief Синглтон работы ПО моделирования метеорной радиосвязи
 * meteor_radio_singleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <patrolsingleton.h>
#include <meteorLoader.h>
#include <meteorWriter.h>
#include "meteorRadioSingleton.h"
#include "meteorRadioStationsFactory.h"

meteorRadioSingleton* meteorRadioSingleton::_instance = nullptr;
PatrolSingleton* meteorRadioSingleton::_patrolInstance = nullptr;

meteorRadioSingleton* meteorRadioSingleton::getMeteorRadioS( QObject* parent ) {
    if( !_instance ) {
        _instance = new meteorRadioSingleton( parent );
        _patrolInstance = PatrolSingleton::getPatrolS( parent );
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
    QObject( parent ), _mrsF( new meteorRadioStationsFactory( parent ) ) {
    if (_instance) {
        qFatal("There should be only one MeteorRadioSingleton object");
    }
    _instance = this;
    qDebug() << __PRETTY_FUNCTION__;
}

meteorRadioSingleton::~meteorRadioSingleton() {
    _instance = nullptr;
    qDebug() << __PRETTY_FUNCTION__;
}
