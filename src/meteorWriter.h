/*
 * @brief Класс, управляющий записью сущностей в БД.
 * meteorWriter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <memory>
#include <QSharedPointer>
#include <patroldbwriter.h>

using std::shared_ptr;

class meteorRadioStation;
class randomNumbersGenerator;

class meteorWriter : public pDBWriter {
public:
    meteorWriter( GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    virtual ~meteorWriter();

    qint64 insertStation( QSharedPointer< meteorRadioStation > mrs ) const;
    qint64 updateStation( QSharedPointer< meteorRadioStation > mrs ) const;
    qint64 deleteStation( QSharedPointer< meteorRadioStation > mrs ) const;

private:
    meteorWriter( const meteorWriter& MW )=delete;
    meteorWriter& operator= (const meteorWriter& MW ) = delete;

    friend class meteorRadioSingleton;

    qint64 insertRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const;
    qint64 updateRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const;
    qint64 deleteRandomGenerator( shared_ptr< randomNumbersGenerator > rng ) const;

private:
    Q_OBJECT
};
