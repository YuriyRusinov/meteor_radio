#include <QApplication>
#include "meteorRadioMainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app( argc, argv );
    QMainWindow* mainW = new MeteorRadioMainWindow;

    mainW->show();
    int ret = app.exec();
    return ret;
}
