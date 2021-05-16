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
class meteorTraceGenerationFactory;

class meteorTraceController : public QObject {
private:
    meteorTraceController( QSharedPointer< int > traceCounter = nullptr, QObject* parent = nullptr );//double aveMeteorAriseFreq, 
    virtual ~meteorTraceController();

public:
    void setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, double elevMin, double elevMax, double scatterMin, double scatterMax );

public slots:
    void handleTraces();
    void startGenerate();
    void stopGenerate();

    void procTraceChannel( QSharedPointer< meteorTraceChannel > mtc );

private slots:
    void workerDestroyed();
//    void threadDestroyed();

signals:
    void traceStart();
    void traceEnd();
    void sendTraceChannel( QSharedPointer< meteorTraceChannel > mtc );

private:
    void traceInit();

private:
    QSharedPointer< int > _tracesCounter;
    meteorTraceWorker* _mTraceW;
    QThread* _mTraceThread;

    double _ariseMathExp;
    double _existanceTimeMathExp;
    double _existanceTimeSt;
    double _aveAmpl;
    double _elevMin;
    double _elevMax;
    double _scatterMin;
    double _scatterMax;

    friend class meteorTraceGenerationFactory;

private:
    Q_OBJECT
};
