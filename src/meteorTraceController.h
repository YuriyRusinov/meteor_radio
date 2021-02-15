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

class meteorTraceController : public QObject {
public:
    meteorTraceController( QObject* parent = nullptr );//double aveMeteorAriseFreq, 
    virtual ~meteorTraceController();

private:
    QThread* _mTraceThread;

    Q_OBJECT
};
