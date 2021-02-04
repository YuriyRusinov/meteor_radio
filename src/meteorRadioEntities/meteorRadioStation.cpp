/*
 * @brief Станция метеорной радиосвязи
 * meteorRadioStation.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <algorithm>
#include <randomNumbGenerator.h>
#include <uniRandomNumbGenerator.h>
#include <expRandomNumbGenerator.h>
#include <gaussianRandomNumbGenerator.h>

#include "meteorRadioStation.h"

using std::make_shared;

meteorRadioStation::meteorRadioStation( long long id, int stationNumber, QString addr, double lon, double lat, int srid, double freq, int stationType )
    : _id( id ),
    _stationNumber( stationNumber ),
    _stationAddress( addr ),
    _longitude( lon ),
    _latitude( lat ),
    _srid( srid ),
    _frequency( freq ),
    _messGen( nullptr ),
    _messagesQueue( queue< shared_ptr<message> > () ),
    _availableAddresses( vector< string > () ) {
    if(stationType < 0 || stationType > 2)
        _stationType = mUnknown;
    else
        _stationType = (meteorRadioStationType)stationType;
}

meteorRadioStation::meteorRadioStation( const meteorRadioStation& MRS )
    : _id( MRS._id ),
    _stationNumber( MRS._stationNumber ),
    _stationAddress( MRS._stationAddress ),
    _longitude( MRS._longitude ),
    _latitude( MRS._latitude ),
    _srid( MRS._srid ),
    _frequency( MRS._frequency ),
    _messGen( MRS._messGen->clone() ) ,
    _stationType( MRS._stationType ),
    _messagesQueue( MRS._messagesQueue ), 
    _availableAddresses( MRS._availableAddresses ) {
}

meteorRadioStation& meteorRadioStation::operator= ( const meteorRadioStation& MRS ) {
    if( &MRS != this ) {
        _id = MRS._id;
        _stationNumber = MRS._stationNumber;
        _stationAddress = MRS._stationAddress;
        _longitude = MRS._longitude;
        _latitude = MRS._latitude;
        _srid = MRS._srid;
        _frequency = MRS._frequency;
        _stationType = MRS._stationType;
        _messGen = MRS._messGen->clone();
        _messagesQueue = MRS._messagesQueue;
        _availableAddresses = MRS._availableAddresses;
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

QString meteorRadioStation::getAddress() const {
    return _stationAddress;
}

void meteorRadioStation::setAddress( QString ipAddr ) {
    _stationAddress = ipAddr;
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

void meteorRadioStation::setMessagesGen( shared_ptr<randomNumbersGenerator> gen ) {
   _messGen = gen;//make_shared< randomNumbersGenerator >( gen->clone() );
}

void meteorRadioStation::clearMessages() {
    queue< shared_ptr<message> > emptyMess;
    std::swap( _messagesQueue, emptyMess );
}

void meteorRadioStation::pushMessage( shared_ptr<message> mess ) {
    _messagesQueue.push( mess );
}

void meteorRadioStation::popMessage() {
    _messagesQueue.pop();
}

size_t meteorRadioStation::messageSize() const {
    return _messagesQueue.size();
}

void meteorRadioStation::clearAddresses() {
    _availableAddresses.clear();
}

void meteorRadioStation::addAddress( const string& addr ) {
    auto ret = std::find_if(_availableAddresses.begin(), _availableAddresses.end(),
    [&addr](const std::string& s) {
        if (s.size() != addr.size())
            return false;
        return std::equal(s.cbegin(), s.cend(), addr.cbegin(), addr.cend(), [](auto c1, auto c2) { return std::toupper(c1) == std::toupper(c2); });
    });
    if( ret != _availableAddresses.end() )
        return;
    _availableAddresses.push_back( addr );
}

string& meteorRadioStation::getAddress( int i ) {
    return _availableAddresses.at( i );
}

const string& meteorRadioStation::getAddress( int i ) const {
    return _availableAddresses.at( i );
}

size_t meteorRadioStation::addrSize() const {
    return _availableAddresses.size();
}
