/*
 * @brief Ребро пути сигнала между станциями метеорной радиосвязи
 * meteorRadioEdge.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorRadioEdge.h"

meteorRadioEdge::meteorRadioEdge( QSharedPointer< meteorRadioStation > _stFrom, QSharedPointer< meteorRadioStation > _stTo )
    : _stationFrom( _stFrom ),
    _stationTo( _stationTo ) {
}

meteorRadioEdge::meteorRadioEdge( const meteorRadioEdge& edge )
    : _stationFrom( edge._stationFrom ),
    _stationTo( edge._stationTo ) {
}

meteorRadioEdge::~meteorRadioEdge() {
}
