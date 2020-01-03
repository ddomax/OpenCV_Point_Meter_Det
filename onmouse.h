#ifndef _ONMOUSE
#define _ONMOUSE

//#ifndef CV_SIMD
//#define CV_SIMD 1
//#endif
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
using namespace cv;
using namespace std;

//1.回调函数签名
void onMouse(int event, int x, int y, int flags, void* param);
void onMouseGetPoint(int event, int x, int y, int flags, void* param);

//2.定义回调函数
void onMouse(int event, int x, int y, int flags, void* param)
{
    Mat *im = reinterpret_cast<Mat*>(param);
    switch (event)
    {
        case CV_EVENT_LBUTTONDOWN:
            std::cout<<"at("<<x<<","<<y<<")value is:"
                <<static_cast<int>(im->at<uchar>(cv::Point(x,y)))<<std::endl;
            break;
        case CV_EVENT_RBUTTONDOWN:
            std::cout<<"input(x,y)"<<endl;
            std::cout<<"x ="<<endl;
            cin>>x;
            std::cout<<"y ="<<endl;
            cin>>y;
            std::cout<<"at("<<x<<","<<y<<")value is:"
                <<static_cast<int>(im->at<uchar>(cv::Point(x,y)))<<std::endl;
            break;
    }
}

void onMouseGetPoint(int event, int x, int y, int flags, void* param)
{
    *((Point*)param) = Point(x,y);
    return;
}

#endif
