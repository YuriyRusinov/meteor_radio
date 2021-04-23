/*
 * @brief Ребро пути сигнала между станциями метеорной радиосвязи
 * meteorRadioEdge.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma	once

#include <QSharedPointer>

class meteorRadioStation;

class meteorRadioEdge {
public:
    meteorRadioEdge( QSharedPointer< meteorRadioStation > _stFrom, QSharedPointer< meteorRadioStation > _stTo );
    meteorRadioEdge( const meteorRadioEdge& edge );
    ~meteorRadioEdge();

private:
    QSharedPointer< meteorRadioStation > _stationFrom;
    QSharedPointer< meteorRadioStation > _stationTo;
};
