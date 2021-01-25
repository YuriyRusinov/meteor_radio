select f_safe_drop_type('h_get_rand');
create type h_get_rand as (id bigint,
                           description varchar,
                           id_distribution bigint,
                           params float8[]);

create or replace function getRandomGen(bigint) returns setof h_get_rand as
$BODY$
declare
    idStationRand alias for $1;

    r h_get_rand%rowtype;
begin

    for r in
        select id, description, id_distribution_func, (select array_agg(a) from unnest(params) a where a is not null ) params from ( select rrr.id, rrr.description, rrr.id_distribution_func,  array_agg(case when rrr.val_min is not null then rrr.val_min else null end) || array_agg(case when rrr.val_max is not null then rrr.val_max else null end) || array_agg(case when rrr.mathematical_expectation_exp is not null then rrr.mathematical_expectation_exp else null end) || array_agg(case when rrr.standard is not null then rrr.standard else null end) || array_agg(case when rrr.scale is not null then rrr.scale else null end) params from tbl_random_gen rrr where rrr.id=idStationRand group by rrr.id ) s
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';
