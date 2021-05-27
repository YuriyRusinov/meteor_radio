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
#include <QDateTime>
#include <QModelIndex>
#include <QSharedPointer>
#include <QObject>
#include <QThread>

#include <memory>

class QAbstractItemView;
class QAbstractItemModel;
class QTimer;

class meteorLoader;
class meteorWriter;
class meteorRadioStation;
class meteorRadioController;
class meteorTraceGenerationFactory;
class meteorTraceChannel;
class meteorReportForm;

class meteorRadioStationsFactory : public QObject {
public:
    QWidget* GUIStationsParameters( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

    double getAveTime() const;
    double getStTime() const;

private slots:
    void addMeteorStation( QAbstractItemModel* stationsModel );
    void editMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void delMeteorStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void refreshStations( QAbstractItemView* stView );

    void saveStationToDb( QSharedPointer< meteorRadioStation > mrs );

    void startModelling( QVector< QSharedPointer< meteorRadioStation > > stations, double distMin, double distMax, double distStep, int nStations,double aveMeteorAriseFreq, double aveMeteorTraceTime, double meteorTraceTimeSt, double aveSignalAmpl, double aveMessageLength, double messageSt, double messSpeed, double elevMin, double elevMax, double scatterMin, double scatterMax );
    void stopModelling();
    void updateResults();

public slots:
    void sendChannelToStations( QSharedPointer< meteorTraceChannel > mtc );

signals:
    void viewRadioParam( QWidget* w );
    void signalModStart();
    void signalModStop();
    void sendTraceParameters( double, double, double, double, double, double, double, double );
    void sendMeteorChannel( QSharedPointer< meteorTraceChannel > mtc );
    void sendReport( int messNum, int bytesNum, int tracesNum, qint64 dtMSec, double aveMeteorTraceTime, double aveMeteorTraceAriseTime, double aveMeteorTracePower, double aveSpeed, double stSpeed );

private:
    meteorRadioStationsFactory( meteorLoader* ml = nullptr, meteorWriter* mw = nullptr, QObject* parent = nullptr );
    meteorRadioStationsFactory( const meteorRadioStationsFactory& ) = delete;
    meteorRadioStationsFactory& operator=( const meteorRadioStationsFactory& ) = delete;
    virtual ~meteorRadioStationsFactory();

    void setTraceGenerationFactory( meteorTraceGenerationFactory* trGenF );

    friend class meteorRadioSingleton;

    QSharedPointer< meteorLoader > _mLoader;
    QSharedPointer< meteorWriter > _mWriter;
    QSharedPointer< meteorRadioController > _mRadioC;
    QSharedPointer< int > _messCount;
    QSharedPointer< int > _allBytesCount;
    meteorTraceGenerationFactory* _mTraceGenFactory;
    QDateTime _dTimeStart;
    QDateTime _dTimeFinish;
    QTimer* _tUpdate;
//    meteorReportForm* _mReportForm;
    //
    // Статистические апостериорные данные
    //
    double _aveDataTime;
    double _stDataTime;

    QAbstractItemModel* _distModel;

private:
    Q_OBJECT
};
