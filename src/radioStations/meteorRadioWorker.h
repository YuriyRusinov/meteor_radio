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
#include <QMutex>

class QTimer;
class meteorRadioStation;
class meteorTraceChannel;

class meteorRadioWorker : public QObject {
public:
    meteorRadioWorker( double messageSpeed = 0.0, QSharedPointer< meteorRadioStation > meteorRadioStaion = nullptr, QSharedPointer< int > messCounter = nullptr, QSharedPointer< int > allCounter = nullptr, QObject* parent = nullptr );
    ~meteorRadioWorker();

public slots:
    void generateMessages();
    void addMessage();
    void stopGen();
    void clearMessagesToChannel( QSharedPointer< meteorTraceChannel > mtc );
    void clearMess();

signals:
    void genMessage( QString message );
    void modellingFinished();
    void sendMessagesNumb( int nmess, int nbyte );
    void sendSpeedValue( int nCurrButesMax );

private:
    QSharedPointer< meteorRadioStation > _meteorRadioStaion;
    QTimer* _tMessage;
    QTimer* _tChannel;
    bool _isRadioRunning;
    double _messageSpeed;
    double _dtMess;
    QSharedPointer< int > _messagesCounter;
    QSharedPointer< int > _allBytesCounter;
    QMutex _stationMutex;

private:
    Q_OBJECT
};
