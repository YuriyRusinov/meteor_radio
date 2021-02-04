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
#include <queue>
#include <vector>

#include "message.h"

using std::shared_ptr;
using std::queue;
using std::vector;

class randomNumbersGenerator;

enum meteorRadioStationType {
    mUnknown = -1,
    mSubscriber = 1, // оконечная станция
    mIntermediate = 2 // промежуточная станция
};

class meteorRadioStation {
public:
    meteorRadioStation( long long id=-1, int stationNumber=-1, QString addr=QString(), double lon=0.0, double lat=0.0, int srid=4326, double freq=-1.0, int stationType = -1 );
    meteorRadioStation( const meteorRadioStation& MRS );
    meteorRadioStation& operator= ( const meteorRadioStation& MRS );
    ~meteorRadioStation();

    long long getId() const;
    void setId( long long id );

    int getStationNumber() const;
    void setStationNumber( int sn );

    QString getAddress() const;
    void setAddress( QString ipAddr );

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
    void setMessagesGen( shared_ptr<randomNumbersGenerator> gen );

    void clearMessages();
    void pushMessage( shared_ptr<message> mess );
    void popMessage();
    size_t messageSize() const;

    void clearAddresses();
    void addAddress( const string& addr );
    string& getAddress( int i );
    const string& getAddress( int i ) const;
    size_t addrSize() const;

private:
    long long _id;
    int _stationNumber;
    QString _stationAddress;
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
    //
    // messages queue
    //
    queue< shared_ptr<message> > _messagesQueue;
    //
    // available addresses
    //
    vector< string > _availableAddresses;
};

Q_DECLARE_METATYPE( meteorRadioStation );
Q_DECLARE_METATYPE( QSharedPointer< meteorRadioStation > );
