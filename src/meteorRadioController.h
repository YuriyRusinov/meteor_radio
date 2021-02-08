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
#include <QSharedPointer>
#include <QVector>
#include <QThread>

class meteorRadioWorker;
class meteorRadioStation;

class meteorRadioController : public QObject {
public:
    meteorRadioController( const QVector< QSharedPointer< meteorRadioStation > >& mStations = QVector< QSharedPointer< meteorRadioStation > >() );
    ~meteorRadioController();

public slots:
    void handleMessages();
    void startMess();
    void stopMess();

signals:
    void operate();
    void finish();

private:
    QVector< QThread* > _messageThreads;

    Q_OBJECT
};
