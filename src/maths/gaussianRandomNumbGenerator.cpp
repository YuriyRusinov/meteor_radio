/*
 * @brief Класс генерации случайных последовательностей с гауссовым (нормальным) распределением
 * gaussianRandomNumbGenerator.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <gsl/gsl_randist.h>
#include <stdexcept>
#include "gaussianRandomNumbGenerator.h"

using std::make_shared;

gaussianRandomNumbersGenerator::gaussianRandomNumbersGenerator( long long id, const gsl_rng_type* rnType, unsigned long seed )
    : randomNumbersGenerator( id, rnType, seed ) {}

gaussianRandomNumbersGenerator::gaussianRandomNumbersGenerator( const gaussianRandomNumbersGenerator& grng )
    : randomNumbersGenerator( grng ) {}

gaussianRandomNumbersGenerator& gaussianRandomNumbersGenerator::operator=( const gaussianRandomNumbersGenerator& grng ) {
    randomNumbersGenerator::operator=( grng );
    return *this;
}

gaussianRandomNumbersGenerator::~gaussianRandomNumbersGenerator() {}

double gaussianRandomNumbersGenerator::generate() const {
    int n = getParamSize();
    if( n < 1 )
        throw std::out_of_range("Cannot set parameters of distribution");
    else if( n == 1 ) {
        double sigma = this->operator[] (0);
        return gsl_ran_gaussian( _rng, sigma );
    }
    else {
        double mu = this->operator[] (0);
        double sigma = this->operator[] (1);
        return mu+gsl_ran_gaussian( _rng, sigma );
    }
}

DistributionFunc gaussianRandomNumbersGenerator::getDistrib() const {
    return DistributionFunc::_Gaussian;
}

shared_ptr< randomNumbersGenerator > gaussianRandomNumbersGenerator::clone() const {
    return make_shared< gaussianRandomNumbersGenerator >( *this );
}
