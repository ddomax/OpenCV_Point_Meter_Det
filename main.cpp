#include <QApplication>
#include <imagprocess.h>
#include <QDebug>
#include <QTimer>
#include <omp.h>
#define LOOP_CAP

int main(int argc, char** argv)
{
//    QApplication a(argc, argv);
    std::cout << "Programme start" << std::endl;
    cv::setNumThreads(2);
    std::cout << "Num of threads:" << cv::getNumThreads() << std::endl;
    if(CV_AVX2)
        std::cout << "AVX2 Supported!" << std::endl;
#ifdef _OPENMP
    printf("OpenMP is supported. Supported version is: %4.2f\n",_OPENMP/100.0);

    int N_PROC = omp_get_num_procs(); // Number of available processors
    printf("Number of available processors: %d\n",N_PROC);

    int MAX_THREADS = omp_get_max_threads(); // Numbers of available threads
    printf("Numbers of available threads: %d\n",MAX_THREADS);

#else
    printf("OpenMP is not supported.");
#endif
    fflush ( stdout );
    ImagProcess processer;
    QTimer captureTimer;
#ifndef LOOP_CAP
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QObject::connect(&captureTimer, SIGNAL(timeout()), &processer, SLOT(process()));
    captureTimer.start(25); // Interval 0 means to refresh as fast as possible
#else
    while(1){
        if(processer.process()<0) return 0;
    }
#endif
//    return a.exec();
}
