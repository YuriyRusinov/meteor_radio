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
    meteorTraceWorker( double ariseM = -1.0, double existanceTime = -1.0, double existanceTimeSt = -1.0, double aveAmpl = -1.0, QObject* parent = nullptr );
    virtual ~meteorTraceWorker();

    void setTraceGenParameters( double ariseM, double existanceTime, double existanceTimeSt, double aveAmpl );

public slots:
    void generateMeteorTraces();
    void addTrace();
    void startTraceGen();
    void stopTraceGen();

signals:
    void traceGenerate( QSharedPointer< meteorTraceChannel > );
    void generationFinished();

private:
    QTimer* _tMeteorTrace;
    bool _isTracesRunning;

    double _ariseMathExp;
    double _existanceTimeMathExp;
    double _existanceTimeSt;
    double _aveAmpl;

    shared_ptr< randomNumbersGenerator > _ariseRng;
    shared_ptr< randomNumbersGenerator > _dtRng;
    shared_ptr< randomNumbersGenerator > _powerRng;

private:
    Q_OBJECT
};