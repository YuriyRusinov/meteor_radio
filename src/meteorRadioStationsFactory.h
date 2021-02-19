/*
 * @brief Фабрика генерации станций связи
 * meteorRadioStationsFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QSharedPointer>
#include <QObject>
#include <QThread>

#include <memory>

class QAbstractItemView;

class meteorLoader;
class meteorWriter;
class meteorRadioStation;
class meteorRadioController;

class meteorRadioStationsFactory : public QObject {
public:
    QWidget* GUIStationsParameters( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

private slots:
    void addMeteorStation( QAbstractItemModel* stationsModel );
    void editMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void delMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void refreshStations( QAbstractItemView* stView );

    void saveStationToDb( QSharedPointer< meteorRadioStation > mrs );

    void startModelling( QVector< QSharedPointer< meteorRadioStation > > stations, double distMin, double distMax, double aveMeteorAriseFreq, double aveMeteorTraceTime, double meteorTraceTimeSt, double aveMessageLength, double messageSt, double messSpeed );
    void stopModelling();

signals:
    void viewRadioParam( QWidget* w );
    void signalModStart();
    void signalModStop();

private:
    meteorRadioStationsFactory( meteorLoader* ml = nullptr, meteorWriter* mw = nullptr, QObject* parent = nullptr );
    meteorRadioStationsFactory( const meteorRadioStationsFactory& ) = delete;
    meteorRadioStationsFactory& operator=( const meteorRadioStationsFactory& ) = delete;
    virtual ~meteorRadioStationsFactory();

    friend class meteorRadioSingleton;

    QSharedPointer< meteorLoader > _mLoader;
    QSharedPointer< meteorWriter > _mWriter;
    QSharedPointer< meteorRadioController > _mRadioC;

private:
    Q_OBJECT
};
