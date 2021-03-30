create or replace function initrand (bigint) returns int4
    as '$libdir/librandgeneration.so', 'initrand' language 'c' strict security definer;

create or replace function droprand () returns int4
    as '$libdir/librandgeneration.so', 'droprand' language 'c' strict security definer;

create or replace function uniformrand() returns float8
    as '$libdir/librandgeneration.so', 'uniformrand' language 'c' strict security definer;

create or replace function exprand(float8) returns float8
    as '$libdir/librandgeneration.so', 'exprand' language 'c' strict security definer;

create or replace function gaussrand(float8) returns float8
    as '$libdir/librandgeneration.so', 'gaussrand' language 'c' strict security definer;

create or replace function rayleighrand(float8) returns float8
    as '$libdir/librandgeneration.so', 'rayleighrand' language 'c' strict security definer;

create or replace function saverand() returns bigint
    as '$libdir/librandgeneration.so', 'saveRand' language 'c' strict security definer;

create or replace function loadrand() returns bigint
    as '$libdir/librandgeneration.so', 'loadRand' language 'c' strict security definer;
