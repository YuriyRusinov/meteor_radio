/*
 * @brief Функции генерации случайных чисел на стороне сервера
 * rand.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdio.h>
#include <postgres.h>
#include <executor/spi.h>
#include "rand.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

gsl_rng * r = 0;

PG_FUNCTION_INFO_V1 (initrand);

RANDOM_EXPORT Datum initrand(PG_FUNCTION_ARGS) {
    r = gsl_rng_alloc (gsl_rng_default);

    unsigned long int seed0 = PG_GETARG_UINT32(0);
    gsl_rng_set (r, seed0);
//    gsl_rng_env_setup();
    PG_RETURN_INT32(0);
}

PG_FUNCTION_INFO_V1 (droprand);

Datum droprand(PG_FUNCTION_ARGS)
{
    if (r)
    {
        gsl_rng_free (r);
        r = 0;
    }
    PG_RETURN_INT32(0);
}

PG_FUNCTION_INFO_V1 (uniformrand);

RANDOM_EXPORT Datum uniformrand(PG_FUNCTION_ARGS) {
    double res = gsl_rng_uniform (r);
    PG_RETURN_FLOAT8(res);
}

PG_FUNCTION_INFO_V1 (exprand);

RANDOM_EXPORT Datum exprand(PG_FUNCTION_ARGS) {
    double alamb = PG_GETARG_FLOAT8 (0);
    if (alamb < 0.1e-15)
    {
        elog(ERROR, "mean of exponential distribution cannot be zero or negative. Please enter valid value.");
        PG_RETURN_NULL();
    }
    double mu = 1.0/alamb;
    double res = gsl_ran_exponential (r, mu);
    PG_RETURN_FLOAT8(res);
}

PG_FUNCTION_INFO_V1 (gaussrand);

RANDOM_EXPORT Datum gaussrand(PG_FUNCTION_ARGS) {
    double sigma = PG_GETARG_FLOAT8 (0);
    if (sigma < 0.0)
    {
        elog(ERROR, "standard of normal distribution cannot be negative. Please enter valid value.");
        PG_RETURN_NULL();
    }
    double res = gsl_ran_gaussian (r, sigma);
    elog(NOTICE, "res=%lf", res);
    PG_RETURN_FLOAT8(res);
}

PG_FUNCTION_INFO_V1 (rayleighrand);

RANDOM_EXPORT Datum rayleighrand(PG_FUNCTION_ARGS) {
    double scale = PG_GETARG_FLOAT8 (0);
    if (scale < 0.0)
    {
        elog(ERROR, "scale of Rayleigh distribution cannot be negative. Please enter valid value.");
        PG_RETURN_NULL();
    }
    double res = gsl_ran_rayleigh( r, scale );
    elog(NOTICE, "res=%lf", res);
    PG_RETURN_FLOAT8(res);
}

PG_FUNCTION_INFO_V1 (saveRand);

RANDOM_EXPORT Datum saveRand(PG_FUNCTION_ARGS) {
    PG_RETURN_INT32( 0 );
}

PG_FUNCTION_INFO_V1 (loadRand);

RANDOM_EXPORT Datum loadRand(PG_FUNCTION_ARGS) {
    PG_RETURN_INT32( 0 );
}
