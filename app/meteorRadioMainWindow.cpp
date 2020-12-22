/*
 * @brief Главный виджет приложения "Meteor-radio"
 * meteorRadioMainWindow.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QMdiArea>
#include <QtDebug>
#include "meteorRadioMainWindow.h"
#include "ui_meteor_radio_main_window.h"

MeteorRadioMainWindow::MeteorRadioMainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
    _UI( new Ui::meteor_radio_main_window ),
    _mdiArea( new QMdiArea ) {
    _UI->setupUi( this );
    setCentralWidget( _mdiArea );

    QObject::connect( _UI->actOpen, &QAction::triggered, this, &MeteorRadioMainWindow::slotOpen );
    QObject::connect( _UI->actStatParameters, &QAction::triggered, this, &MeteorRadioMainWindow::slotStationsParameters );
    QObject::connect( _UI->actQuit, &QAction::triggered, this, &QMainWindow::close );
}

MeteorRadioMainWindow::~MeteorRadioMainWindow() {
    delete _mdiArea;
    delete _UI;
}

void MeteorRadioMainWindow::slotOpen() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MeteorRadioMainWindow::slotStationsParameters() {
    qDebug() << __PRETTY_FUNCTION__;
}
