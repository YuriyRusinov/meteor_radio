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

/*
RANDOM_EXPORT Datum initrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum droprand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum uniformrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum exprand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum gaussrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum rayleighrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum saveRand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum loadRand(PG_FUNCTION_ARGS);
*/
