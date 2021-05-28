/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <math.h>
#include <gsl/gsl_statistics_double.h>

#include <meteorTraceChannel.h>
#include "meteorTraceGenerationFactory.h"
#include "meteorTraceController.h"
#include "meteorRadioStationsFactory.h"
#include "meteor_constants.h"

using std::vector;

QSharedPointer< meteorTraceChannel > meteorTraceGenerationFactory::generate() const {
    return nullptr;
}

meteorTraceGenerationFactory::meteorTraceGenerationFactory( QObject* parent )
    : QObject( parent ),
    _mRSF( nullptr ),
    _traceCounter( new int (0) ),
    _mTraceController( new meteorTraceController( _traceCounter ) ),
    _aveMeteorDurationTraceTime( 0.0 ),
    _aveMeteorAriseTime( 0.0 ),
    _stMeteorTraceTime( 0.0 ),
    _aveMeteorTracePower( 0.0 ),
    _ariseTime( vector< double >() ),
    _stDistances( vector< double >() ) {
    QObject::connect( _mTraceController, &meteorTraceController::sendTraceChannel, this, &meteorTraceGenerationFactory::retransmitMeteorTrace, Qt::DirectConnection );
}

meteorTraceGenerationFactory::~meteorTraceGenerationFactory() {
    qDebug() << __PRETTY_FUNCTION__ << *_traceCounter;
    _mTraceController->stopGenerate();
    delete _mTraceController;//->deleteLater();
}

void meteorTraceGenerationFactory::setStationFactory( meteorRadioStationsFactory* rsf ) {
    _mRSF = rsf;
    QObject::connect( _mRSF,
                      &meteorRadioStationsFactory::signalModStop,
                      this,
                      &meteorTraceGenerationFactory::stopTraceGen );

    QObject::connect( _mRSF,
                      &meteorRadioStationsFactory::sendTraceParameters,
                      this,
                      &meteorTraceGenerationFactory::setTraceParameters );

    QObject::connect( this,
                      &meteorTraceGenerationFactory::sendTrace,
                      _mRSF,
                      &meteorRadioStationsFactory::sendChannelToStations,
                      Qt::DirectConnection );
}

void meteorTraceGenerationFactory::stopTraceGen() {
    qDebug() << __PRETTY_FUNCTION__ << *_traceCounter;
    _mTraceController->stopGenerate();
}

void meteorTraceGenerationFactory::setTraceParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, double elevMin, double elevMax, double scatterMin, double scatterMax ) {
    _ariseMathExp = ariseM;
    _existanceTimeMathExp = existanceTime;
    _existanceTimeSt = existanceTimeSt;
    _aveAmpl = aveAmpl;
    qDebug() << __PRETTY_FUNCTION__ << _ariseMathExp << _existanceTimeMathExp << _existanceTimeSt << _aveAmpl << elevMin << elevMax << scatterMin << scatterMax;
    _mTraceController->setTraceGenParameters( _ariseMathExp, _existanceTimeMathExp, _existanceTimeSt,_aveAmpl, elevMin, elevMax, scatterMin, scatterMax );
    _mTraceController->startGenerate();
}

void meteorTraceGenerationFactory::retransmitMeteorTrace( QSharedPointer< meteorTraceChannel > mtc ) {
    int nd = _stDistances.size();
    for( int id=0; id<nd; id++) {
        double phi = mtc->getElevationAngle()*_pi/180.0;
        double dt = _stDistances[id] / cos(phi) / _speed_of_light;
        qDebug() << __PRETTY_FUNCTION__ << dt;
        double tArise = mtc->getAriseTime() + dt;
        _ariseTime.push_back( tArise );
        _aveMeteorAriseTime += tArise;
        _aveMeteorDurationTraceTime += mtc->getTimeTrace();
        _aveMeteorTracePower += mtc->getChannelPower();
        int nt = _ariseTime.size();
        if( nt > 1 ) {
    //        qDebug() << __PRETTY_FUNCTION__ << _ariseTime;
            double * wd = new double [ nt ];
            for( int i=0; i<nt; i++ ) 
                wd[i] = _ariseTime[i];

            double mean = gsl_stats_mean( wd, 1, nt );
            _aveTime[id] = mean;
            _stMeteorTraceTime = sqrt( gsl_stats_variance_m( wd, 1, nt, mean ) );
            _stTime[id] = _stMeteorTraceTime;
            delete [] wd;
    //        qDebug() << __PRETTY_FUNCTION__ << mean << getAveAriseTime() << _stMeteorTraceTime << nt;
        }
    }
    emit sendTrace( mtc );
}

int meteorTraceGenerationFactory::getTracesNumber() const {
    if( _traceCounter.isNull() )
        return -1;

    return *_traceCounter;
}

double meteorTraceGenerationFactory::getAveAriseTime() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorAriseTime/(*_traceCounter );
}

double meteorTraceGenerationFactory::getAveDurationTime() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorDurationTraceTime/(*_traceCounter );
}

double meteorTraceGenerationFactory::getAvePower() const {
    if ( getTracesNumber() <= 0 )
        return 0.0;

    return _aveMeteorTracePower/(*_traceCounter );
}

double meteorTraceGenerationFactory::getStArise() const {
    return _stMeteorTraceTime;
}

void meteorTraceGenerationFactory::setDistances( const Matrix& matrDist ) {
    _mDistances = matrDist;
    _stDistances.clear();
    _aveTime.clear();
    _stTime.clear();
    int nr = _mDistances.rowCount();
    int nc = _mDistances.columnCount();
    for( int i=0; i<nr; i++ )
        for( int j=i+1; j<nc; j++ ) {
            double dist = _mDistances(i, j);
            _stDistances.push_back( dist );
            _aveTime.push_back( 0.0 );
            _stTime.push_back( 0.0 );
        }
}

const vector< double >& meteorTraceGenerationFactory::getDistances() const {
    return _stDistances;
}

const vector< double >& meteorTraceGenerationFactory::getAveTime() const {
    return _aveTime;
}

const vector< double >& meteorTraceGenerationFactory::getStTime() const {
    return _stTime;
}
