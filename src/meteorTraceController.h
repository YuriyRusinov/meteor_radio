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

class QThread;
class meteorTraceWorker;

class meteorTraceController : public QObject {
public:
    meteorTraceController( QObject* parent = nullptr );//double aveMeteorAriseFreq, 
    virtual ~meteorTraceController();

private:
    meteorTraceWorker* _mTraceW;
    QThread* _mTraceThread;

private:
    Q_OBJECT
};
