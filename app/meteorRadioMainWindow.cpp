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
#include <QHostAddress>
#include <QToolBar>
#include <QtDebug>

#include <gsl/gsl_matrix.h>

#include <matrix.h>
#include <meteorRadioSingleton.h>
#include <meteorRadioStationsFactory.h>
#include <patrolsingleton.h>
#include <patrolguiapp.h>
#include <vector.h>

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
    QHostAddress testAddr("192.168.10.129");
    Q_IPV6ADDR addr6 = testAddr.toIPv6Address();
    bool ok;
    quint32 addr4 = testAddr.toIPv4Address( &ok );
//    qDebug() << __PRETTY_FUNCTION__ << sizeof( addr6 ) << sizeof( addr4 );
//    for (int i = 0; i < 16; ++i) {
//        qDebug() << __PRETTY_FUNCTION__ << addr6[i] << sizeof(addr6[i]);
//    }

/*     double a[] = { 0.11, 0.12, 0.13,
                 0.21, 0.22, 0.23 };
    Matrix aM( a, 2, 3 );
    double b[] = { 1011, 1012,
                 1021, 1022,
                 1031, 1032 };
    Matrix bM( b, 3, 2 );
    double c[] = { 0.00, 0.00,
                 0.00, 0.00 };
    Matrix cM( aM );
    cM *= bM;
    qDebug() << __PRETTY_FUNCTION__ << QString("Matrix C");
    for( int i=0; i<2; i++ )
        for( int j=0; j<2; j++ )
            qDebug() << __PRETTY_FUNCTION__ << cM(i, j);
*/
    double a_data[] = { 0.18, 0.60, 0.57, 0.96,
                      0.41, 0.24, 0.99, 0.58,
                      0.14, 0.30, 0.97, 0.66,
                      0.51, 0.13, 0.19, 0.85 };
    Matrix A( a_data, 4, 4 );

    double b_data[] = { 1.0, 2.0, 3.0, 4.0 };
    Vector B( b_data, 4 );

    Vector X = solveSystem( A, B );
    for (int i=0; i<4; i++)
        qDebug() << __PRETTY_FUNCTION__ << X(i);

    qDebug() << __PRETTY_FUNCTION__;
    Vector C = A*X;
    for (int i=0; i<4; i++)
        qDebug() << __PRETTY_FUNCTION__ << C(i);

    initActions();
    setEnabled( false );
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    QObject::connect( pGuiApp, &PatrolGuiApp::disconnected, this, &MeteorRadioMainWindow::slotDbDisconnected );

    meteorRadioStationsFactory* mrsF = _mrs->getMRS();
    QObject::connect( mrsF, &meteorRadioStationsFactory::viewRadioParam, this, &MeteorRadioMainWindow::slotAddWidget );

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
    mrsF->GUIStationsParameters();
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
