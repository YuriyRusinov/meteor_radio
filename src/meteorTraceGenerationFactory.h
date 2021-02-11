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

class meteorTraceChannel;

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

    friend class meteorRadioSingleton;
private:
    Q_OBJECT
};
