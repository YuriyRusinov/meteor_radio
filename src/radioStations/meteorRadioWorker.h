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

class QTimer;
class meteorRadioStation;
class meteorTraceChannel;

class meteorRadioWorker : public QObject {
public:
    meteorRadioWorker( QSharedPointer< meteorRadioStation > meteorRadioStaion = nullptr );
    ~meteorRadioWorker();

public slots:
    void generateMessages();
    void addMessage();
    void stopGen();
    void clearMessagesToChannel( QSharedPointer< meteorTraceChannel > mtc );

signals:
    void genMessage( QString message );
    void modellingFinished();

private:
    QSharedPointer< meteorRadioStation > _meteorRadioStaion;
    QTimer* _tMessage;
    bool _isRadioRunning;

private:
    Q_OBJECT
};
