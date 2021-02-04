/*
 * @brief Класс генерации тестовых сообщений для станций метеорной связи
 * meteorRadioWorker.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>

class meteorRadioWorker : public QObject {
public:
    meteorRadioWorker();
    ~meteorRadioWorker();

public slots:
    void generateMessages();

signals:
    void modellingFinished();

private:
    Q_OBJECT
};
