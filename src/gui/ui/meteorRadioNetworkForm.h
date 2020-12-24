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

class QAbstractItemModel;

namespace Ui {
    class meteor_radio_network_form;
}

enum DistributionFunctions {
    Exponential = 0,
    Gaussjan = 1,
    Uniform = 2
};

class meteorRadioNetworkForm : public QWidget {
public:
    meteorRadioNetworkForm( QWidget* parent = nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    virtual ~meteorRadioNetworkForm();

    void setStationsModel( QAbstractItemModel* stationsModel );

private slots:
    void addStation();
    void editStation();
    void delStation();

    void startModelling();
    void close();

signals:
    void addMRStation( QAbstractItemModel* stationsModel );
    void editMRStation( const QModelIndex& wIndex, QAbstractItemModel* stationsModel );
    void delMRStation( const QModelIndex& wIndex );

private:
    Ui::meteor_radio_network_form* _UI;

private:
    Q_OBJECT
};
