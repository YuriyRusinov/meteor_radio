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
    if (!r)
        PG_RETURN_INT32(-1);
    size_t nr = gsl_rng_size (r);
    bytea* randBuffer = (bytea *)palloc(nr*sizeof(bytea));
    FILE* fRand = fmemopen( randBuffer, nr, "wb");
    if( fRand == NULL )
        PG_RETURN_INT32(-2);
    int res = gsl_rng_fwrite (fRand, r);
    if (res != 0)
        PG_RETURN_INT32 (res);
    int spi_res = SPI_connect();
    if(spi_res != SPI_OK_CONNECT)
    {
        elog(ERROR, "Cannot connect via SPI");
        PG_RETURN_INT32(-3);
    }
    fclose (fRand);
    size_t nr_ins = strlen ("insert into tbl_random_states (id, random_state, rand_seed) values ();")+nr*sizeof( *randBuffer )+2*sizeof(long)+100;
    char* r_sql = (char *) palloc( nr_ins + 1);
    const int nargs = 3;
    char *nulls = (char *)(palloc (nargs*sizeof(char)));
    nulls[0] = ' ';
    nulls[1] = ' ';
    nulls[2] = ' ';
    Oid * oids = (Oid *)palloc (nargs*sizeof (Oid));
    oids[0] = INT8OID;
    oids[1] = BYTEAOID;
    oids[2] = INT8OID;
    Datum * vals = (Datum *)palloc (nargs*sizeof (Datum));
    vals[0] = Int32GetDatum(-1);
    const char* seqSql = "select getnextseq(\'tbl_random_states\', \'id\');";
    int rseq = SPI_execute( seqSql, true, 1 );
    int idproc = SPI_processed;
    if (rseq != SPI_OK_SELECT || idproc != 1)
    {
        SPI_finish ();
        pfree (randBuffer);
        PG_RETURN_INT32 (-4);
    }
    long int id;
    TupleDesc tupdesc = SPI_tuptable->tupdesc;
    SPITupleTable *tuptable = SPI_tuptable;
    HeapTuple tuple = tuptable->vals[0];
    char * id_str = SPI_getvalue (tuple, tupdesc, 1);
    id = atol (id_str);
    elog (INFO, "result id=%ld\n", id);
    vals[0] = Int32GetDatum(id);
    vals[1] = PointerGetDatum (randBuffer);
    unsigned long long seed = gsl_rng_get (r);
    snprintf (r_sql, nr_ins+100, "insert into tbl_random_states (id, random_state, rand_seed) values ($1, $2, $3);");//, id, randBuffer, seed);
    vals[2] = Int64GetDatum (seed);

    elog (INFO, "value=%d id=%ld\n", DatumGetInt32 (vals[0]), id);
    elog (INFO, "%s\n", r_sql);
    int rins = SPI_execute_with_args (r_sql, nargs, oids, vals, nulls, false, 1L);
    // SPI_execute (r_sql, false, 1L);
    if (rins != SPI_OK_INSERT)
    {
        SPI_finish ();
        elog(ERROR, "Cannot insert random numbers generation via SPI");
        pfree (oids);
        pfree (vals);
        PG_RETURN_INT32 (rins);
    }
    pfree( randBuffer );
    pfree( oids );
    pfree( vals );
    SPI_finish();
    PG_RETURN_INT32(id);
}

PG_FUNCTION_INFO_V1 (loadRand);

RANDOM_EXPORT Datum loadRand(PG_FUNCTION_ARGS) {
    PG_RETURN_INT32( 0 );
}
