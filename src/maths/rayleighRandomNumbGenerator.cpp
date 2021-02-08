/*
 * @brief Класс генерации случайных последовательностей с распределением Релея
 * rayleighRandomNumbGenerator.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <gsl/gsl_randist.h>
#include <stdexcept>
#include "rayleighRandomNumbGenerator.h"

using std::make_shared;
using std::shared_ptr;

rayleighRandomNumbersGenerator::rayleighRandomNumbersGenerator( long long id, const gsl_rng_type* rnType, unsigned long seed )
    : randomNumbersGenerator( id, rnType, seed ) {
}

rayleighRandomNumbersGenerator::rayleighRandomNumbersGenerator( const rayleighRandomNumbersGenerator& rrng )
    : randomNumbersGenerator( rrng ) {}

rayleighRandomNumbersGenerator& rayleighRandomNumbersGenerator::operator=( const rayleighRandomNumbersGenerator& rrng ) {
    randomNumbersGenerator::operator=( rrng );
    return *this;
}
    
rayleighRandomNumbersGenerator::~rayleighRandomNumbersGenerator() {}

double rayleighRandomNumbersGenerator::generate() const {
    int n = getParamSize();
    if( n < 1 )
        throw std::out_of_range("Cannot set parameters of distribution");
    else {
        double sigma = this->operator[] (0);
        return gsl_ran_rayleigh( _rng, sigma );
    }
}

DistributionFunc rayleighRandomNumbersGenerator::getDistrib() const {
    return DistributionFunc::_Rayleigh;
}

shared_ptr< randomNumbersGenerator > rayleighRandomNumbersGenerator::clone() const {
    return make_shared< rayleighRandomNumbersGenerator >( *this );
}
