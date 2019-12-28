#include <QApplication>
#include <imagprocess.h>
#include <QDebug>
#include <QTimer>
#define LOOP_CAP

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ImagProcess processer;
    QTimer captureTimer;
#ifndef LOOP_CAP
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QObject::connect(&captureTimer, SIGNAL(timeout()), &processer, SLOT(process()));
    captureTimer.start(25); // Interval 0 means to refresh as fast as possible
#else
    while(1){
        processer.process();
        if(waitKey(1)==27)
            return 0;//ESC for quit
    }
#endif
    return a.exec();
}
