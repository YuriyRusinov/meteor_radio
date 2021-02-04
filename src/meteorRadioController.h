/*
 * @brief Класс контроллер генерации тестовых сообщений для станций метеорной связи
 * meteorRadioController.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>
#include <QThread>

class meteorRadioWorker;

class meteorRadioController : public QObject {
public:
    meteorRadioController();
    ~meteorRadioController();
private:
    QThread messThread;

    Q_OBJECT
};
