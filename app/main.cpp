#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtDebug>

#include "meteorRadioMainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app( argc, argv );
    QTranslator * meteorTr = new QTranslator (0);
/*    QLocale meteorLocale( QLocale::Russian );
    bool isTr = meteorTr->load( QString("./transl/meteor_radio_ru") );
    qDebug() << __PRETTY_FUNCTION__ << isTr;
    bool isInstalled = QCoreApplication::installTranslator( meteorTr );
    qDebug() << __PRETTY_FUNCTION__ << isInstalled;*/
    QMainWindow* mainW = new MeteorRadioMainWindow;

    mainW->show();
    int ret = app.exec();
    delete mainW;
    return ret;
}
