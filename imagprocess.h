#ifndef IMAGPROCESS_H
#define IMAGPROCESS_H

//#ifndef CV_SIMD
//#define CV_SIMD 1
//#endif
//#define CV_AVX2 1
#include <QObject>
#include <QApplication>
#include<iostream>
#include<math.h>
#include <omp.h>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/imgproc/types_c.h"
#include <opencv2/videoio/videoio.hpp>
#include "opencv2/videoio/videoio_c.h"
#include <QDebug>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "mtexttovoice.h"
#include "circlefinder.h"
using namespace std;
using namespace cv;

class ImagProcess : public QObject
{
    Q_OBJECT
public:
    explicit ImagProcess(QObject *parent = nullptr);
    ~ImagProcess();

signals:

private:
    Mat ChooseROI(Mat src_img, Mat template_img, Mat dst_img);
    Mat HoughCircle(Mat gray_img, Mat midd_img);
    Mat HoughLine(Mat midd_img, Mat midd_line_image);
    static const int RECORD_DATA_LEN = 100;
    int recordX[RECORD_DATA_LEN];
    int recordY[RECORD_DATA_LEN];
    int recordR[RECORD_DATA_LEN];
    int recordX1[RECORD_DATA_LEN];
    int recordY1[RECORD_DATA_LEN];
    int recordR1[RECORD_DATA_LEN];
    int recordX2[RECORD_DATA_LEN];
    int recordY2[RECORD_DATA_LEN];
    int recordR2[RECORD_DATA_LEN];
    double dataAverage(int *recordData,int num = RECORD_DATA_LEN);
    void addData(int *recordData,int dataIn);
    void lockTargets(int targetNum=1);
    void openSerialPort();
    void refreshSerialPorts();
    float CalculateValue();
    void recordCircle();

    Point circle_center;
    int circle_radius;

    Vec4i l;
    Vec4i cho_l;

    VideoCapture cap;
    VideoWriter writer;
    QTime time;

    int frameWidth,frameHeight;
    static const int thLaser = 100;

    QSerialPort* m_serial;
    QStringList portList;
    MTextToVoice mtts;
    int xTarget,yTarget,r;
    QByteArray speed = QByteArray(4,(uchar)0);
    bool startMove = false;
    CircleFinder finder;
    int curTargetNum = 2;

public slots:
    int process();
};

#endif // IMAGPROCESS_H
