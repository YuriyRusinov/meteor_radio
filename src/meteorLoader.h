/*
 * @brief Загрузчик сущностей из БД
 * meteorLoader.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QVector>
#include <QSharedPointer>
#include <patroldbloader.h>

class meteorRadioStation;

class meteorLoader : public pDBLoader {
public:
    meteorLoader( GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    ~meteorLoader();

    QVector< QSharedPointer< meteorRadioStation > > loadStations() const;

private:
    Q_OBJECT
};
