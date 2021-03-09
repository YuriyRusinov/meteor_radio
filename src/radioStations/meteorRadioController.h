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
class meteorTraceChannel;

class meteorRadioController : public QObject {
public:
    meteorRadioController( const QVector< QSharedPointer< meteorRadioStation > >& mStations = QVector< QSharedPointer< meteorRadioStation > >(), QObject* parent = nullptr );
    ~meteorRadioController();

private slots:
    void handleMessages();
    void startMess();
    void stopMess();
    void getMeteorTrace( QSharedPointer< meteorTraceChannel > mtc );

signals:
    void operate();
    void finish();
    void sendTraceToStations( QSharedPointer< meteorTraceChannel > mtc );

private:
    QThread* _stationsThread;
    QVector< meteorRadioWorker* > _mStationsW;

    friend class meteorRadioStationsFactory;

    Q_OBJECT
};
