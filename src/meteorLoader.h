/*
 * @brief Загрузчик сущностей из БД
 * meteorLoader.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <memory>

#include <QVector>
#include <QSharedPointer>
#include <patroldbloader.h>

using std::shared_ptr;
class meteorRadioStation;
class randomNumbersGenerator;

class meteorLoader : public pDBLoader {
public:
    meteorLoader( GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    ~meteorLoader();

    QVector< QSharedPointer< meteorRadioStation > > loadStations() const;
    double distance( QSharedPointer< meteorRadioStation > st1, QSharedPointer< meteorRadioStation > st2 ) const;

private:
    friend class meteorRadioSingleton;
    shared_ptr< randomNumbersGenerator > loadStatRandomGen( qint32 idRandGen ) const;

private:
    Q_OBJECT
};
