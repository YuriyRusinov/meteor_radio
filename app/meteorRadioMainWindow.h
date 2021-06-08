/*
 * @brief Главный виджет приложения "Meteor-radio"
 * meteorRadioMainWindow.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QMainWindow>

class QMdiArea;
class QToolBar;

namespace Ui {
    class meteor_radio_main_window;
}

class meteorRadioSingleton;
class PatrolSingleton;

class MeteorRadioMainWindow : public QMainWindow {
public:
    MeteorRadioMainWindow( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~MeteorRadioMainWindow();

private slots:
    void slotDbConnect();
    void slotDbDisconnect();
    void slotDbDisconnected();

    void slotOpen();
    void slotStationsParameters();

    void slotAddWidget(QWidget* w);
    void slotSortRes();

private:
    //
    // Functions
    //
    void initActions();
    void setEnabled(bool enable);
   
private:
    //
    // Variables
    //
    Ui::meteor_radio_main_window* _UI;
    QToolBar* _tbAct;
    QMdiArea* _mdiArea;
    meteorRadioSingleton* _mrs;
    PatrolSingleton* _patrolS;

private:
    Q_OBJECT
};

