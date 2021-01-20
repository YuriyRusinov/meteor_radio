create or replace function insertMeteorRadioStation(bigint, varchar, smallint, float8, float8, integer, float8, bigint ) returns bigint as
$BODY$
declare
    sNumber alias for $1;
    sAddr alias for $2;
    sType alias for $3;
    sLongitude alias for $4;
    sLatitude alias for $5;
    sSrid alias for $6;
    sFreq alias for $7;
    sMessageGen alias for $8;

    stId bigint;
begin
    select getnextseq('tbl_meteor_station', 'id') into stId;
    insert into tbl_meteor_station(id, station_number, station_address, station_type, longitude, latitude, srid, frequency, id_message_gen) values( stId, sNumber, sAddr, sType, sLongitude, sLatitude, sSrid, sFreq, sMessageGen );
    if (NOT FOUND) then
       return -1;
    end if;

    return stId; 

end
$BODY$
language 'plpgsql' security definer;

create or replace function updateMeteorRadioStation( bigint, bigint, varchar, smallint, float8, float8, integer, float8, bigint) returns bigint as
$BODY$
declare
    stId alias for $1;
    sNumber alias for $2;
    sAddr alias for $3;
    sType alias for $4;
    sLongitude alias for $5;
    sLatitude alias for $6;
    sSrid alias for $7;
    sFreq alias for $8;
    sMessageGen alias for $9;
begin

    update tbl_meteor_station set station_number = sNumber,
                                  station_address = sAddr,
                                  station_type = sType,
                                  longitude = sLongitude,
                                  latitude = sLatitude,
                                  srid = sSrid,
                                  frequency = sFreq,
                                  id_message_gen = sMessageGen
                                where id = stId;

    if( not FOUND ) then
        return -1;
    end if;

    return stId;

end
$BODY$
language 'plpgsql';

create or replace function delMeteorRadioStation( bigint ) returns bigint as
$BODY$
declare
    stId alias for $1;

begin

    delete from tbl_meteor_station where id = stId;
    if( not FOUND ) then
        return -1;
    end if;

    return stId;
end
$BODY$
language 'plpgsql';
