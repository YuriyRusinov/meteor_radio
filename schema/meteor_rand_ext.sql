create or replace function initrand (bigint) returns int4
    as '$libdir/librandgeneration.so', 'initrand' language 'c' strict security definer;

create or replace function droprand () returns int4
    as '$libdir/librandgeneration.so', 'droprand' language 'c' strict security definer;


