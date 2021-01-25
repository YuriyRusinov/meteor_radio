/*
 * @brief Класс генерации случайных последовательностей с гауссовым (нормальным) распределением
 * gaussianRandomNumbGenerator.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once
#include <memory>
#include <QSharedPointer>
#include "randomNumbGenerator.h"

class gaussianRandomNumbersGenerator : public randomNumbersGenerator {
public:
    gaussianRandomNumbersGenerator( long long id = -1, const gsl_rng_type* rnType = gsl_rng_default, unsigned long seed = gsl_rng_default_seed );
    gaussianRandomNumbersGenerator( const gaussianRandomNumbersGenerator& grng );
    gaussianRandomNumbersGenerator& operator=( const gaussianRandomNumbersGenerator& grng );
    virtual ~gaussianRandomNumbersGenerator();

    double generate() const override;
    DistributionFunc getDistrib() const override;
    shared_ptr< randomNumbersGenerator > clone() const;
};
