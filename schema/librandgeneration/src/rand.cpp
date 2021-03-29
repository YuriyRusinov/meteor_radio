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
#include "rand.h"

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

/*
RANDOM_EXPORT Datum uniformrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum exprand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum gaussrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum rayleighrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum saveRand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum loadRand(PG_FUNCTION_ARGS);
*/
