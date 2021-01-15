/*
 * @brief Класс генерации случайных последовательностей с экспоненциальным распределением
 * expRandomNumbGenerator.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <gsl/gsl_randist.h>
#include "expRandomNumbGenerator.h"

using std::make_shared;

expRandomNumbersGenerator::expRandomNumbersGenerator( long long id, const gsl_rng_type* rnType, unsigned long seed )
    : randomNumbersGenerator( id, rnType, seed ) {}

expRandomNumbersGenerator::expRandomNumbersGenerator( const expRandomNumbersGenerator& erng )
    : randomNumbersGenerator( erng ) {}

expRandomNumbersGenerator& expRandomNumbersGenerator::operator=( const expRandomNumbersGenerator& erng ) {
    randomNumbersGenerator::operator=( erng );
    return *this;
}

expRandomNumbersGenerator::~expRandomNumbersGenerator() { }

double expRandomNumbersGenerator::generate() const {
    if( getParamSize() == 0 ) {
        // needs 1 parameter
        return -1.0;
    }
    double wval = gsl_ran_exponential( _rng, at(0) );
    return wval;
}

DistributionFunc expRandomNumbersGenerator::getDistrib() const {
    return DistributionFunc::_Exponential;
}

shared_ptr< randomNumbersGenerator > expRandomNumbersGenerator::clone() const {
    return make_shared< expRandomNumbersGenerator > (*this);
}
