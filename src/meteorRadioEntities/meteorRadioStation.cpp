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

using std::make_shared;

meteorRadioStation::meteorRadioStation( long long id, int stationNumber, double lon, double lat, int srid, double freq, int stationType )
    : _id( id ),
    _stationNumber( stationNumber ),
    _longitude( lon ),
    _latitude( lat ),
    _srid( srid ),
    _frequency( freq ),
    _messGen( nullptr ) {
    if(stationType < 0 || stationType > 2)
        _stationType = mUnknown;
    else
        _stationType = (meteorRadioStationType)stationType;
}

meteorRadioStation::meteorRadioStation( const meteorRadioStation& MRS )
    : _id( MRS._id ),
    _stationNumber( MRS._stationNumber ),
    _longitude( MRS._longitude ),
    _latitude( MRS._latitude ),
    _srid( MRS._srid ),
    _frequency( MRS._frequency ),
    _messGen( MRS._messGen->clone() ) ,
    _stationType( MRS._stationType ) {
/*    if( MRS._messGen != nullptr ) {
        DistributionFunc mdf = MRS._messGen->getDistrib();
        switch( mdf ) {
            case DistributionFunc::_Undefined: default: _messGen = nullptr; break;
            case DistributionFunc::_Uniform: _messGen.reset( new uniRandomNumbersGenerator( *dynamic_cast<uniRandomNumbersGenerator *>(MRS._messGen) )); break;
            case DistributionFunc::_Exponential: _messGen.reset ( new expRandomNumbersGenerator( *dynamic_cast<expRandomNumbersGenerator *>(MRS._messGen) ) ); break;
            case DistributionFunc::_Gaussian: _messGen.reset ( new gaussianRandomNumbersGenerator( *dynamic_cast<gaussianRandomNumbersGenerator *>(MRS._messGen) )); break;
        }
    }*/
}

meteorRadioStation& meteorRadioStation::operator= ( const meteorRadioStation& MRS ) {
    if( &MRS != this ) {
        _id = MRS._id;
        _stationNumber = MRS._stationNumber;
        _longitude = MRS._longitude;
        _latitude = MRS._latitude;
        _srid = MRS._srid;
        _frequency = MRS._frequency;
        _stationType = MRS._stationType;
        _messGen = MRS._messGen->clone();
    }
    return *this;
}

meteorRadioStation::~meteorRadioStation() {
    _messGen.reset();
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

meteorRadioStationType meteorRadioStation::getType() const {
    return _stationType;
}

void meteorRadioStation::setType( meteorRadioStationType _type ) {
    _stationType = _type;
}

shared_ptr< randomNumbersGenerator > meteorRadioStation::getMessagesGen() const {
    return _messGen;
}

void meteorRadioStation::setMessagesGen( randomNumbersGenerator* gen ) {
   _messGen = gen->clone();//make_shared< randomNumbersGenerator >( gen->clone() );
}
