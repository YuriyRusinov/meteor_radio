/*
 * @brief Класс генерации метеорных следов для станций метеорной связи
 * meteorTraceWorker.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>
#include <QSharedPointer>
#include <randomNumbGenerator.h>
#include <memory>

class QTimer;
class meteorTraceChannel;

using std::shared_ptr;

class meteorTraceWorker : public QObject {
public:
    meteorTraceWorker( QSharedPointer< int > tracesCounter = nullptr, double ariseM = -1.0, double existanceTime = -1.0, double existanceTimeSt = -1.0, double aveAmpl = -1.0, QObject* parent = nullptr );
    virtual ~meteorTraceWorker();

    void setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl, double elevMin, double elevMax, double scatterMin, double scatterMax );

public slots:
    void generateMeteorTraces();
    void addTrace();
    void startTraceGen();
    void stopTraceGen();

signals:
    void traceGenerate( QSharedPointer< meteorTraceChannel > );
    void generationFinished();

private:
    QSharedPointer< int > _tracesCounter;
    QTimer* _tMeteorTrace;
    bool _isTracesRunning;

    double _ariseMathExp;
    double _existanceTimeMathExp;
    double _existanceTimeSt;
    double _aveAmpl;
    double _elevMin;
    double _elevMax;
    double _scatterMin;
    double _scatterMax;

    shared_ptr< randomNumbersGenerator > _ariseRng;
    shared_ptr< randomNumbersGenerator > _dtRng;
    shared_ptr< randomNumbersGenerator > _powerRng;
    shared_ptr< randomNumbersGenerator > _elevRng;
    shared_ptr< randomNumbersGenerator > _scatterRng;

private:
    Q_OBJECT
};
