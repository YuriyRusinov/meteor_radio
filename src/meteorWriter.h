/*
 * @brief Класс, управляющий записью сущностей в БД.
 * meteorWriter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSharedPointer>
#include <patroldbwriter.h>

class meteorRadioStation;

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
private:
    Q_OBJECT
};
