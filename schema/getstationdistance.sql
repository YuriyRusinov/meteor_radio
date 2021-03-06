create or replace function calcStationDist(bigint, bigint, integer) returns float8 as
$BODY$
declare
    idStation1 alias for $1;
    idStation2 alias for $2;
    srid0 alias for $3;

    query varchar;
    result float8;
    cnt1 integer;
    cnt2 integer;
begin
    select into cnt1 count(*) from tbl_meteor_station where id=idStation1;
    select into cnt2 count(*) from tbl_meteor_station where id=idStation2;
    if( cnt1 = 0 or cnt2 = 0 ) then
        return null;
    end if;
    if(srid0 is null) then
        query := E'select st_distance(st_GeographyFromText(\'SRID=\'|| r.srid || \';\' || \'POINT(\' || r.longitude || \' \' || r.latitude || \')\'), st_GeographyFromText(\'SRID=\'|| r1.srid || \';\' || \'POINT(\' || r1.longitude || \' \' || r1.latitude || \')\')  ) from ( select srid,longitude,latitude from tbl_meteor_station where id = ' || idStation1 || E') as r, (select srid,longitude,latitude from tbl_meteor_station where id = ' || idStation2 || E') as r1;';
    else
        query := E'select st_distance(St_transform (GeomFromEWKT(\'SRID=\' || r.srid || \';\' || \'POINT(\' || r.longitude || \' \' || r.latitude || \')\'),' || srid0 || E'), St_transform (GeomFromEWKT(\'SRID=\' || r1.srid || \';\' || \'POINT(\' || r1.longitude || \' \' || r1.latitude || \')\'), ' || srid0 || E') ) from ( select srid,longitude,latitude from tbl_meteor_station where id = ' || idStation1 || E' ) as r, (select srid,longitude,latitude from tbl_meteor_station where id = ' || idStation2 || E') as r1;';
    end if;
    execute query into result;

    return result;
end
$BODY$
language 'plpgsql';
