/*
 * @brief Класс генерации случайных последовательностей с экспоненциальным распределением
 * expRandomNumbGenerator.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "randomNumbGenerator.h"

class expRandomNumbersGenerator : public randomNumbersGenerator {
public:
    expRandomNumbersGenerator( const gsl_rng_type* rnType = gsl_rng_default, unsigned long seed = gsl_rng_default_seed );
    expRandomNumbersGenerator( const expRandomNumbersGenerator& erng );
    expRandomNumbersGenerator& operator=( const expRandomNumbersGenerator& erng );
    virtual ~expRandomNumbersGenerator();

    double generate() const override;
    DistributionFunc getDistrib() const override;
};