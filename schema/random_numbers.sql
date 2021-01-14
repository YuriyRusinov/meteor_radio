create or replace function insertRandomParams( bigint, float8, float8 ) returns integer as
$BODY$
declare
    idDistrib alias for $1;
    param1 alias for $2;
    param2 alias for $3;

    idRand bigint;
begin
end
$BODY$
language 'plpgsql';
