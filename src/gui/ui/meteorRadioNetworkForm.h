/*
 * @brief Форма задания исходных параметров станций и метеорных потоков
 * meteorRadioNetworkForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QModelIndex>
#include <QWidget>
#include <QSharedPointer>
#include <QVector>

class QAbstractItemModel;
class QAbstractItemView;

namespace Ui {
    class meteor_radio_network_form;
}

class meteorRadioStation;

class meteorRadioNetworkForm : public QWidget {
public:
    meteorRadioNetworkForm( QWidget* parent = nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    virtual ~meteorRadioNetworkForm();

    void setStationsModel( QAbstractItemModel* stationsModel );

private slots:
    void addStation();
    void editStation();
    void delStation();
    void refreshStations();

    void startModelling();
    void stopModelling();
    void close();

signals:
    void addMRStation( QAbstractItemModel* stationsModel );
    void editMRStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void delMRStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void refreshStationModel( QAbstractItemView* stationsView );

    void beginModelling( QVector< QSharedPointer< meteorRadioStation > > stations, double distMin, double distMax, double distStep, int nStations,  double aveMeteorAriseFreq, double aveMeteorTraceTime, double stMeteorTraceTime, double signalAveAmpl, double aveMessageLength, double messageSt, double messSpeed, double mElevMin, double mElevMax, double mScatterMin, double mScatterMax );
    void finishModelling();

private:
    void init();

private:
    Ui::meteor_radio_network_form* _UI;

private:
    Q_OBJECT
};
