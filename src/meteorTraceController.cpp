/*
 * @brief Класс контроллер потока генерации следов метеоров
 * meteorTraceController.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QThread>
#include "meteorTraceWorker.h"
#include "meteorTraceController.h"

meteorTraceController::meteorTraceController( QObject* parent )
    : QObject( parent ),
    _mTraceW( new meteorTraceWorker ),
    _mTraceThread( new QThread ) {
    _mTraceW->moveToThread( _mTraceThread );
}

meteorTraceController::~meteorTraceController() {
    _mTraceThread->deleteLater();
}
