/*
 * @brief Станция метеорной радиосвязи
 * meteorRadioStation.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QMetaType>
#include <QSharedPointer>
#include <memory>

using std::shared_ptr;

class randomNumbersGenerator;

enum meteorRadioStationType {
    mUnknown = -1,
    mSubscriber = 0, // оконечная станция
    mIntermediate = 1 // промежуточная станция
};

class meteorRadioStation {
public:
    meteorRadioStation( long long id=-1, int stationNumber=-1, double lon=0.0, double lat=0.0, int srid=4326, double freq=-1.0, int stationType = -1 );
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

    meteorRadioStationType getType() const;
    void setType( meteorRadioStationType _type );

    shared_ptr< randomNumbersGenerator > getMessagesGen() const;
    void setMessagesGen( randomNumbersGenerator * gen );
private:
    long long _id;
    int _stationNumber;
    double _longitude;
    double _latitude;
    int _srid;

    double _frequency;

    //
    // messages generator;
    //
    shared_ptr< randomNumbersGenerator > _messGen;
    //
    // station type
    //
    meteorRadioStationType _stationType;
};

Q_DECLARE_METATYPE( meteorRadioStation );
Q_DECLARE_METATYPE( QSharedPointer< meteorRadioStation > );
