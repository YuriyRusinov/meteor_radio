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
#include <QSharedPointer>

class meteorRadioStation;

class meteorRadioWorker : public QObject {
public:
    meteorRadioWorker( QSharedPointer< meteorRadioStation > meteorRadioStaion = nullptr );
    ~meteorRadioWorker();

public slots:
    void generateMessages();

signals:
    void genMessage( QString message );
    void modellingFinished();

private:
    QSharedPointer< meteorRadioStation > _meteorRadioStaion;

private:
    Q_OBJECT
};
