/*
 * @brief Класс генерации случайных последовательностей с равномерным распределением
 * uniRandomNumbGenerator.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "uniRandomNumbGenerator.h"

uniRandomNumbersGenerator::uniRandomNumbersGenerator( const gsl_rng_type* rnType, unsigned long seed )
    : randomNumbersGenerator( rnType, seed ) {}

uniRandomNumbersGenerator::uniRandomNumbersGenerator( const uniRandomNumbersGenerator& urng )
    : randomNumbersGenerator( urng ) {}

uniRandomNumbersGenerator& uniRandomNumbersGenerator::operator=( const uniRandomNumbersGenerator& urng ) {
    randomNumbersGenerator::operator=( urng );
    return *this;
}

uniRandomNumbersGenerator::~uniRandomNumbersGenerator() {
}

double uniRandomNumbersGenerator::generate() const {
    double wval = gsl_rng_uniform( _rng );
    if(getParamSize() <= 1)
        return wval;
    double xmin = at( 0 );
    double xmax = at( 1 );
    return xmin + (xmax - xmin)*wval;
}
