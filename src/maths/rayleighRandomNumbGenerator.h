/*
 * @brief Класс генерации случайных последовательностей с распределением Релея
 * rayleighRandomNumbGenerator.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "randomNumbGenerator.h"

class rayleighRandomNumbersGenerator : public randomNumbersGenerator {
public:
    rayleighRandomNumbersGenerator( long long id = -1, const gsl_rng_type* rnType = gsl_rng_default, unsigned long seed = gsl_rng_default_seed );
    rayleighRandomNumbersGenerator( const rayleighRandomNumbersGenerator& rrng );
    rayleighRandomNumbersGenerator& operator=( const rayleighRandomNumbersGenerator& rrng );
    virtual ~rayleighRandomNumbersGenerator();

    double generate() const override;
    DistributionFunc getDistrib() const override;
    shared_ptr< randomNumbersGenerator > clone() const override;
};
