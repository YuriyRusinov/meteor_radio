create or replace function insertRandomParams( bigint, float8, float8 ) returns integer as
$BODY$
declare
    idDistrib alias for $1;
    param1 alias for $2;
    param2 alias for $3;

    idRand bigint;
begin
    select getNextSeq('tbl_random_gen', 'id') into idRand;
    case idDistrib
    when 1 then
        insert into tbl_random_gen (id, id_distribution_func, val_min, val_max) values (idRand, idDistrib, param1, param2);
    when 2 then
        insert into tbl_random_gen (id, id_distribution_func, mathematical_expectation_exp) values (idRand, idDistrib, param1);
    when 3 then
        insert into tbl_random_gen (id, id_distribution_func, mathematical_expectation, standard) values (idRand, idDistrib, param1, param2);
    when 4 then
        insert into tbl_random_gen (id, id_distribution_func, scale) values (idRand, idDistrib, param1);
    else
        return -1;
    end case;

    return idRand;
end
$BODY$
language 'plpgsql';

create or replace function updateRandomParams( bigint, bigint, float8, float8 ) returns integer as
$BODY$
declare
    idRand alias for $1;
    idDistrib alias for $2;
    param1 alias for $3;
    param2 alias for $4;

begin
    case idDistrib
    when 1 then
        update tbl_random_gen set id_distribution_func = idDistrib,
                                  val_min = param1,
                                  val_max = param2,
                                  mathematical_expectation_exp = null::float8,
                                  mathematical_expectation = null::float8,
                                  standard = null::float8,
                                  scale = null::float8
                                where id = idRand;
    when 2 then
        update tbl_random_gen set id_distribution_func = idDistrib,
                                  mathematical_expectation_exp = param1,
                                  val_min = null::float8,
                                  val_max = null::float8,
                                  mathematical_expectation = null::float8,
                                  standard = null::float8,
                                  scale = null::float8
                                where id = idRand;
    when 3 then
        update tbl_random_gen set id_distribution_func = idDistrib,
                                  mathematical_expectation = param1,
                                  standard = param2,
                                  val_min = null::float8,
                                  val_max = null::float8,
                                  mathematical_expectation_exp = null::float8,
                                  scale = null::float8
                                where id = idRand;
    when 4 then
        update tbl_random_gen set id_distribution_func = idDistrib,
                                  mathematical_expectation = null::float8,
                                  standard = null::float8,
                                  val_min = null::float8,
                                  val_max = null::float8,
                                  mathematical_expectation_exp = null::float8,
                                  scale = param1
                                where id = idRand;
    else
        return -1;
    end case;

    return idRand;
end
$BODY$
language 'plpgsql';

create or replace function deleteRandomParams( bigint ) returns integer as
$BODY$
declare
    idRand alias for $1;
begin
    delete from tbl_random_gen where id = idRand;

    if( not FOUND ) then
        return -1;
    else
        return idRand;
    end if;
end
$BODY$
language 'plpgsql';
