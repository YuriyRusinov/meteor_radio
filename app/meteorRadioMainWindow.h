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

namespace Ui {
    class meteor_radio_main_window;
}

class QMdiArea;

class MeteorRadioMainWindow : public QMainWindow {
public:
    MeteorRadioMainWindow( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~MeteorRadioMainWindow();

private slots:
    void slotOpen();
    void slotStationsParameters();

private:
    Ui::meteor_radio_main_window* _UI;
    QMdiArea* _mdiArea;

private:
    Q_OBJECT
};

