/*
 * @brief Класс контроллер потока генерации следов метеоров
 * meteorTraceController.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QThread>
#include "meteorTraceController.h"

meteorTraceController::meteorTraceController( QObject* parent )
    : QObject( parent ),
    _mTraceThread( new QThread ) {
    }

meteorTraceController::~meteorTraceController() {
    _mTraceThread->deleteLater();
}
