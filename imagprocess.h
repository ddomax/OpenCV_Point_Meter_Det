#ifndef IMAGPROCESS_H
#define IMAGPROCESS_H

#include <QObject>
#include <QApplication>
#include<iostream>
#include<math.h>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"
#include <opencv2/videoio/videoio.hpp>
#include "opencv2/videoio/videoio_c.h"
#include <QDebug>
#include <QTime>
using namespace std;
using namespace cv;

class ImagProcess : public QObject
{
    Q_OBJECT
public:
    explicit ImagProcess(QObject *parent = nullptr);

signals:

private:
    Mat ChooseROI(Mat src_img, Mat template_img, Mat dst_img);
    Mat HoughCircle(Mat gray_img, Mat midd_img);
    Mat HoughLine(Mat midd_img, Mat midd_line_image);
    float CalculateValue();

    Point circle_center;
    int circle_radius;

    Vec4i l;
    Vec4i cho_l;

    VideoCapture cap;
    QTime time;

public slots:
    int process();
};

#endif // IMAGPROCESS_H
