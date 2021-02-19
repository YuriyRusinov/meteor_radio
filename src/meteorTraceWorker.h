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

class meteorTraceChannel;

class meteorTraceWorker : public QObject {
public:
    meteorTraceWorker( QObject* parent = nullptr );
    virtual ~meteorTraceWorker();

public slots:
    void generateMeteorTraces();
    void startTraceGen();
    void stopTraceGen();

signals:
    void traceGenerate( QSharedPointer< meteorTraceChannel > );
    void generationFinished();

private:
private:
    Q_OBJECT
};
