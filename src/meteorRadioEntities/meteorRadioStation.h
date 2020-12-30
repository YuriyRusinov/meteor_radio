/*
 * @brief Станция метеорной радиосвязи
 * meteorRadioStation.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class meteorRadioStation {
public:
    meteorRadioStation( long long id=-1, int stationNumber=-1, double lon=0.0, double lat=0.0, int srid=4326, double freq=-1.0 );
    meteorRadioStation( const meteorRadioStation& MRS );
    meteorRadioStation& operator= ( const meteorRadioStation& MRS );
    ~meteorRadioStation();

    long long getId() const;
    void setId( long long id );

    int getStationNumber() const;
    void setStationNumber( int sn );

    double getLongitude() const;
    void setLongitude( double lon );

    double getLatitude() const;
    void setLatitude( double lat );

    int getSrid() const;
    void setSrid( int srid );

    double getFrequency() const;
    void setFrequency( double freq );
private:
    long long _id;
    int _stationNumber;
    double _longitude;
    double _latitude;
    int _srid;

    double _frequency;
};
