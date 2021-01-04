/*
 * @brief Класс генерации случайных последовательностей с равномерным распределением
 * uniRandomNumbGenerator.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "randomNumbGenerator.h"

class uniRandomNumbersGenerator : public randomNumbersGenerator {
public:
    uniRandomNumbersGenerator( const gsl_rng_type* rnType = gsl_rng_default, unsigned long seed = gsl_rng_default_seed );
    uniRandomNumbersGenerator( const uniRandomNumbersGenerator& urng );
    uniRandomNumbersGenerator& operator=( const uniRandomNumbersGenerator& urng );
    virtual ~uniRandomNumbersGenerator();

    double generate() const override;
    DistributionFunc getDistrib() const override;
};
