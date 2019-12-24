#include <QApplication>
#include <imagprocess.h>
#include <QDebug>
#include <QTimer>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ImagProcess processer;
    QTimer captureTimer;
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QObject::connect(&captureTimer, SIGNAL(timeout()), &processer, SLOT(process()));
    captureTimer.start(0); // Interval 0 means to refresh as fast as possible

    return a.exec();
}
