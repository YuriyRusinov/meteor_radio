create or replace function insertMeteorRadioStation(bigint, smallint, float8, float8, integer, float8, bigint) returns bigint as
$BODY$
declare
    sNumber alias for $1;
    sType alias for $2;
    sLongitude alias for $3;
    sLatitude alias for $4;
    sSrid alias for $5;
    sFreq alias for $6;
    sMessageGen alias for $7;

    stId bigint;
begin
    select getnextseq('tbl_meteor_station', 'id') into stId;
    insert into tbl_meteor_station(id, station_number, station_type, longitude, latitude, srid, frequency, id_message_gen) values( stId, sNumber, sType, sLongitude, sLatitude, sSrid, sFreq, sMessageGen );
    if (NOT FOUND) then
       return -1;
    end if;

    return stId; 

end
$BODY$
language 'plpgsql' security definer;
