/*
 * @brief Главный виджет приложения "Meteor-radio"
 * meteorRadioMainWindow.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QtDebug>
#include <meteorRadioSingleton.h>
#include <meteorRadioStationsFactory.h>
#include <patrolsingleton.h>
#include "meteorRadioMainWindow.h"
#include "ui_meteor_radio_main_window.h"

MeteorRadioMainWindow::MeteorRadioMainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
    _UI( new Ui::meteor_radio_main_window ),
    _mdiArea( new QMdiArea ) {
    _UI->setupUi( this );
    setCentralWidget( _mdiArea );
    _mrs = meteorRadioSingleton::getMeteorRadioS();
    PatrolSingleton* _patrolS = PatrolSingleton::getPatrolS();
    QObject::connect( _UI->actOpen, &QAction::triggered, this, &MeteorRadioMainWindow::slotOpen );
    QObject::connect( _UI->actStatParameters, &QAction::triggered, this, &MeteorRadioMainWindow::slotStationsParameters );
    QObject::connect( _UI->actQuit, &QAction::triggered, this, &QMainWindow::close );
}

MeteorRadioMainWindow::~MeteorRadioMainWindow() {
    qDebug() << __PRETTY_FUNCTION__;
    delete _mdiArea;
    delete _UI;
    meteorRadioSingleton::resetMRS();
}

void MeteorRadioMainWindow::slotOpen() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MeteorRadioMainWindow::slotStationsParameters() {
    qDebug() << __PRETTY_FUNCTION__;
    meteorRadioStationsFactory* mrsF = _mrs->getMRS();
    QWidget * mrsW = mrsF->GUIStationsParameters();
    slotAddWidget( mrsW );
}

void MeteorRadioMainWindow::slotAddWidget(QWidget* w) {
    if (!w)
        return;

    w->setAttribute(Qt::WA_DeleteOnClose);
    QMdiSubWindow * subW = _mdiArea->addSubWindow(w);
    subW->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}
