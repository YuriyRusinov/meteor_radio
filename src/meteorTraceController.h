/*
 * @brief Класс контроллер потока генерации следов метеоров
 * meteorTraceController.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>
#include <QSharedPointer>

class QThread;
class meteorTraceWorker;
class meteorTraceChannel;

class meteorTraceController : public QObject {
public:
    meteorTraceController( QObject* parent = nullptr );//double aveMeteorAriseFreq, 
    virtual ~meteorTraceController();

    void setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl );

public slots:
    void handleTraces();
    void startGenerate();
    void stopGenerate();

    void procTraceChannel( QSharedPointer< meteorTraceChannel > mtc );

signals:
    void traceStart();
    void traceEnd();

private:
    void traceInit();

private:
    meteorTraceWorker* _mTraceW;
    QThread* _mTraceThread;

    double _ariseMathExp;
    double _existanceTimeMathExp;
    double _existanceTimeSt;
    double _aveAmpl;

private:
    Q_OBJECT
};
