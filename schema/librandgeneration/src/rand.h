/*
 * @brief Функции генерации случайных чисел на стороне сервера
 * rand.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

//#ifdef PG_MODULE_MAGIC
//PG_MODULE_MAGIC;
//#endif

#include <postgres.h>
#include <funcapi.h>
#include <fmgr.h>
#include <catalog/pg_type.h>
#include <executor/spi.h>
#include <sys/stat.h>
#include <utils/builtins.h>
#include "random_config.h"

RANDOM_EXPORT Datum initrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum droprand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum uniformrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum exprand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum gaussrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum rayleighrand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum saveRand(PG_FUNCTION_ARGS);
RANDOM_EXPORT Datum loadRand(PG_FUNCTION_ARGS);

