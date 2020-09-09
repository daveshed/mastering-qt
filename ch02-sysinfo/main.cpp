#include <QApplication>

#include "MainWindow.h"
#include "sysinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // initialise the sysinfo singleton
    SysInfo::instance().init();
    MainWindow w;
    w.show();
    return a.exec();
}
