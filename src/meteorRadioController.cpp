/*
 * @brief Класс контроллер генерации тестовых сообщений для станций метеорной связи
 * meteorRadioController.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "meteorRadioController.h"

meteorRadioController::meteorRadioController() {
    messThread.start();
}

meteorRadioController::~meteorRadioController() {
    messThread.quit();
    messThread.wait();
}
