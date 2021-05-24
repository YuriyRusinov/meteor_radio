create or replace function addMessageToStation( varchar, bytea, bigint ) returns bigint as
$BODY$
declare
    address alias for $1;
    content alias for $2;
    id_from alias for $3;

    idSent bigint;
    idMessage bigint;
begin

    select into idSent id from tbl_meteor_station where lower(station_address) = lower(address);
    if( idSent is null ) then
        raise warning 'Cannot find station with address %', address;
        return -1;
    elsif( idSent = id_from ) then
        raise warning 'Cannot send message to the same station';
        return -1;
    end if;
    select into idMessage getnextseq('tbl_meteor_messages', 'id');
    insert into tbl_meteor_messages( id, message_content, id_meteor_station_from, id_meteor_station_to ) values ( idMessage, content, id_from, idSent );
    if( not FOUND ) then
        raise warning 'Cannot insert message';
        return -2;
    end if;

    return idMessage;
    exception when others then
        return -3;
end
$BODY$
language 'plpgsql';
