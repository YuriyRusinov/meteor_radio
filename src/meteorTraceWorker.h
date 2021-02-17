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

class meteorTraceChannel;

class meteorTraceWorker : public QObject {
public:
    meteorTraceWorker( QObject* parent = nullptr );
    virtual ~meteorTraceWorker();

public slots:
    void generateMeteorTrace();

signals:
    void traceGenerate( QSharedPointer< meteorTraceChannel > );

private:
    Q_OBJECT
};
