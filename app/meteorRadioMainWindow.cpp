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
#include <QToolBar>
#include <QtDebug>

#include <meteorRadioSingleton.h>
#include <meteorRadioStationsFactory.h>
#include <patrolsingleton.h>
#include <patrolguiapp.h>
#include "meteorRadioMainWindow.h"
#include "ui_meteor_radio_main_window.h"

MeteorRadioMainWindow::MeteorRadioMainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
    _UI( new Ui::meteor_radio_main_window ),
    _tbAct( new QToolBar ),
    _mdiArea( new QMdiArea ) {
    _UI->setupUi( this );
    this->addToolBar(Qt::TopToolBarArea, _tbAct);
    setCentralWidget( _mdiArea );
    _mrs = meteorRadioSingleton::getMeteorRadioS();
    _patrolS = meteorRadioSingleton::getPatrol();//PatrolSingleton::getPatrolS();

    initActions();
    setEnabled( false );
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    QObject::connect( pGuiApp, &PatrolGuiApp::disconnected, this, &MeteorRadioMainWindow::slotDbDisconnected );

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

void MeteorRadioMainWindow::slotDbConnect() {
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    QMap<int, QString> accLevels;
    QStringList secLevels;
    secLevels << tr("Not secret") << tr("Confidential") << tr("Secret") << tr("Top secret");
    for(int i=0; i<secLevels.size(); i++)
        accLevels.insert(i, secLevels[i]);
    bool isConn = pGuiApp->GUIConnect(accLevels);
    setEnabled( isConn );
}

void MeteorRadioMainWindow::slotDbDisconnect() {
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    pGuiApp->disconnectFromDb();
}

void MeteorRadioMainWindow::slotDbDisconnected() {
    setEnabled( false );
}

void MeteorRadioMainWindow::initActions() {
    _UI->actConnect_to_DB->setIcon(QIcon(":/patrol/db_connect.png"));
    _tbAct->addAction( _UI->actConnect_to_DB );
    _UI->actConnect_to_DB->setToolTip(tr("Connect to database"));
    QObject::connect( _UI->actConnect_to_DB, &QAction::triggered, this, &MeteorRadioMainWindow::slotDbConnect );

    _UI->act_Disconnect_from_DB->setIcon(QIcon(":/patrol/db_disconnect.png"));
    _tbAct->addAction( _UI->act_Disconnect_from_DB );
    _UI->act_Disconnect_from_DB->setToolTip(tr("Disconnect from database"));
    QObject::connect( _UI->act_Disconnect_from_DB, &QAction::triggered, this, &MeteorRadioMainWindow::slotDbDisconnect);
    _tbAct->addSeparator();

    _UI->actQuit->setIcon(QIcon(":/patrol/exit.png"));
    _tbAct->addAction(_UI->actQuit);
    QObject::connect(_UI->actQuit, &QAction::triggered, this, &QMainWindow::close);
}

void MeteorRadioMainWindow::setEnabled(bool enable) {
    _UI->menu_Stations->setEnabled( enable );
    _UI->actOpen->setEnabled( enable );
}
