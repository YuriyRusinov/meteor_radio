/*
 * @brief Синглтон работы ПО моделирования метеорной радиосвязи
 * meteor_radio_singleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QCoreApplication>
#include <QDir>
#include <QTranslator>
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
        _patrolInstance->installTranslator();
        _instance = new meteorRadioSingleton( parent );
        _instance->installTranslator();
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
    _mTrGF ( new meteorTraceGenerationFactory ),
    _meteorTor( new QTranslator( nullptr ) ) {
    if (_instance) {
        qFatal("There should be only one MeteorRadioSingleton object");
    }
    _instance = this;
    _mTrGF->setStationFactory( _mrsF );
    _mrsF->setTraceGenerationFactory( _mTrGF );
    bool isLoaded = _meteorTor->load(QString("./transl/meteor_radio_ru") );
    if( isLoaded )
        QCoreApplication::installTranslator( _meteorTor );

    qDebug() << __PRETTY_FUNCTION__;
}

meteorRadioSingleton::~meteorRadioSingleton() {
    _instance = nullptr;
    delete _mTrGF;
    delete _mrsF;
    delete _meteorTor;
    qDebug() << __PRETTY_FUNCTION__;
}

void meteorRadioSingleton::installTranslator() const {
    QString translPath = QDir::currentPath()+QDir::separator()+QString("transl");
    QString translFile = QString("meteor_radio_ru");

    bool isLoaded = _meteorTor->load(translFile, translPath);
    qDebug() << __PRETTY_FUNCTION__ << isLoaded << translPath << translFile;
    if( isLoaded ) {
        bool isInst = QCoreApplication::installTranslator( _meteorTor );
        qDebug() << __PRETTY_FUNCTION__ << isInst;
    }

}
