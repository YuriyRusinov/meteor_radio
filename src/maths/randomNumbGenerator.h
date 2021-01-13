/*
 * @brief Класс генерации случайных последовательностей
 * randomNumbGenerator.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <memory>
#include <vector>
#include <gsl/gsl_rng.h>

using std::vector;
using std::shared_ptr;

enum DistributionFunc {
    _Undefined = -1,
    _Uniform = 0,
    _Exponential = 1,
    _Gaussian = 2
};

class randomNumbersGenerator {
public:
    randomNumbersGenerator( const gsl_rng_type* rnType = gsl_rng_default, unsigned long seed = gsl_rng_default_seed );
    randomNumbersGenerator( const randomNumbersGenerator& rng );
    randomNumbersGenerator& operator=( const randomNumbersGenerator& rng );
    virtual ~randomNumbersGenerator();

    void setSeed( unsigned long seed );

    void clearParamValues();
    void addParamValue( double value );
    size_t getParamSize() const;
    const double& operator[] ( const int& i ) const;
    double& operator[] ( const int& i );
    const double& at( const int& i ) const;
    double& at( const int& i );

    virtual double generate() const=0;
    virtual DistributionFunc getDistrib() const;
    virtual shared_ptr< randomNumbersGenerator > clone() const=0;

protected:
    gsl_rng* _rng;

private:
    vector< double > _params;
};
