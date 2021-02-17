/*
 * @brief Фабрика генерации следов метеоров подходящих для радиосвязи
 * meteorTraceGenerationFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>
#include <QSharedPointer>
#include <memory>

class meteorTraceChannel;
class meteorRadioStationsFactory;
class meteorTraceController;

using std::unique_ptr;
using std::weak_ptr;

class meteorTraceGenerationFactory : public QObject {
public:
    QSharedPointer< meteorTraceChannel > generate() const;

signals:
    void sendTrace( QSharedPointer< meteorTraceChannel > );

private:
    meteorTraceGenerationFactory( QObject* parent = nullptr );
    meteorTraceGenerationFactory( const meteorTraceGenerationFactory& MTGF ) = delete;
    meteorTraceGenerationFactory& operator=( const meteorTraceGenerationFactory& MTGF ) = delete;
    virtual ~meteorTraceGenerationFactory();

    void setStationFactory( meteorRadioStationsFactory* rsf );

    friend class meteorRadioSingleton;
    meteorRadioStationsFactory* _mRSF;
    meteorTraceController* _mTraceController;

private:
    Q_OBJECT
};
