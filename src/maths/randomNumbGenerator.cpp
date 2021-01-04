/*
 * @brief Класс генерации случайных последовательностей
 * randomNumbGenerator.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "randomNumbGenerator.h"

randomNumbersGenerator::randomNumbersGenerator( const gsl_rng_type* rnType, unsigned long seed )
    : _params( vector< double >() ) {
    _rng = gsl_rng_alloc( rnType );
    gsl_rng_env_setup();
    gsl_rng_set( _rng, seed );
}

randomNumbersGenerator::randomNumbersGenerator( const randomNumbersGenerator& rng )
    : _params( rng._params ) {
    _rng = gsl_rng_clone( rng._rng );
}

randomNumbersGenerator& randomNumbersGenerator::operator=( const randomNumbersGenerator& rng ) {
    if( this != &rng ) {
        gsl_rng_memcpy(_rng, rng._rng);
        _params = rng._params;
    }
    return *this;
}

randomNumbersGenerator::~randomNumbersGenerator() {
    gsl_rng_free( _rng );
}

void randomNumbersGenerator::setSeed( unsigned long seed ) {
    gsl_rng_set( _rng, seed );
}

void randomNumbersGenerator::clearParamValues() {
    _params.clear();
}

void randomNumbersGenerator::addParamValue( double value ) {
    _params.push_back( value );
}

size_t randomNumbersGenerator::getParamSize() const {
    return _params.size();
}

const double& randomNumbersGenerator::operator[] ( const int& i ) const {
    return _params[i];
}

double& randomNumbersGenerator::operator[] ( const int& i ) {
    return _params[i];
}

const double& randomNumbersGenerator::at( const int& i ) const {
    return _params.at(i);
}

double& randomNumbersGenerator::at( const int& i ) {
    return _params.at(i);
}

DistributionFunc randomNumbersGenerator::getDistrib() const {
    return DistributionFunc::_Undefined;
}
