/*
 * @brief Станция метеорной радиосвязи
 * meteorRadioStation.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <randomNumbGenerator.h>
#include <uniRandomNumbGenerator.h>
#include <expRandomNumbGenerator.h>
#include <gaussianRandomNumbGenerator.h>

#include "meteorRadioStation.h"

meteorRadioStation::meteorRadioStation( long long id, int stationNumber, double lon, double lat, int srid, double freq )
    : _id( id ),
    _stationNumber( stationNumber ),
    _longitude( lon ),
    _latitude( lat ),
    _srid( srid ),
    _frequency( freq ),
    _messGen( nullptr ) {
}

meteorRadioStation::meteorRadioStation( const meteorRadioStation& MRS )
    : _id( MRS._id ),
    _stationNumber( MRS._stationNumber ),
    _longitude( MRS._longitude ),
    _latitude( MRS._latitude ),
    _srid( MRS._srid ),
    _frequency( MRS._frequency ),
    _messGen( nullptr ) {
    if( MRS._messGen != nullptr ) {
        DistributionFunc mdf = MRS._messGen->getDistrib();
        switch( mdf ) {
            case DistributionFunc::_Undefined: default: _messGen = nullptr; break;
            case DistributionFunc::_Uniform: _messGen = new uniRandomNumbersGenerator( *dynamic_cast<uniRandomNumbersGenerator *>(MRS._messGen) ); break;
            case DistributionFunc::_Exponential: _messGen = new expRandomNumbersGenerator( *dynamic_cast<expRandomNumbersGenerator *>(MRS._messGen) ); break;
            case DistributionFunc::_Gaussian: _messGen = new gaussianRandomNumbersGenerator( *dynamic_cast<gaussianRandomNumbersGenerator *>(MRS._messGen) ); break;
        }
    }
}

meteorRadioStation& meteorRadioStation::operator= ( const meteorRadioStation& MRS ) {
    if( &MRS != this ) {
        _id = MRS._id;
        _stationNumber = MRS._stationNumber;
        _longitude = MRS._longitude;
        _latitude = MRS._latitude;
        _srid = MRS._srid;
        _frequency = MRS._frequency;
    }
    return *this;
}

meteorRadioStation::~meteorRadioStation() {
    delete _messGen;
}

long long meteorRadioStation::getId() const {
    return _id;
}

void meteorRadioStation::setId( long long id ) {
    _id = id;
}

int meteorRadioStation::getStationNumber() const {
    return _stationNumber;
}

void meteorRadioStation::setStationNumber( int sn ) {
    _stationNumber = sn;
}

double meteorRadioStation::getLongitude() const {
    return _longitude;
}

void meteorRadioStation::setLongitude( double lon ) {
    _longitude = lon;
}

double meteorRadioStation::getLatitude() const {
    return _latitude;
}

void meteorRadioStation::setLatitude( double lat ) {
    _latitude = lat;
}

int meteorRadioStation::getSrid() const {
    return _srid;
}

void meteorRadioStation::setSrid( int srid ) {
    _srid = srid;
}

double meteorRadioStation::getFrequency() const {
    return _frequency;
}

void meteorRadioStation::setFrequency( double freq ) {
    _frequency = freq;
}
