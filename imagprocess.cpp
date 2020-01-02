#include "imagprocess.h"
#include "circlefinder.h"
#include "onmouse.h"
#include <iostream>
#include <omp.h>
using namespace std;

ImagProcess::ImagProcess(QObject *parent) : QObject(parent)
{
    openSerialPort();
    cap = VideoCapture(0+cv::CAP_DSHOW); //cv::CAP_DSHOW
    cap.open(0+cv::CAP_DSHOW);
    //检查摄像头是否成功打开
    if (!cap.isOpened())
    {
        qDebug()<<"摄像头未成功打开"<<endl;
    }
//    cap.set(cv::CAP_PROP_FOURCC,cv::FOURCC('M', 'J', 'P', 'G'));
//    qDebug() << cap.get(cv::CAP_PROP_FOURCC);
//    qDebug() << cap.set(cv::CAP_PROP_FOURCC,CV_FOURCC('Y', 'U', 'Y', '2'));
//    qDebug() << cap.get(cv::CAP_PROP_FOURCC);
    qDebug() << cap.set(cv::CAP_PROP_FRAME_WIDTH, 10000); //1024*3 2592 3840
    qDebug() << cap.set(cv::CAP_PROP_FRAME_HEIGHT, 10000); //768*3  1944 2880

    frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH); //1024*3
    frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //768*3
    qDebug() << QString("Resolution:%1x%2").arg(frameWidth).arg(frameHeight);
//    qDebug() << cap.set(cv::CAP_PROP_CONVERT_RGB, 0);
//    qDebug() << cap.set(cv::CAP_PROP_AUTO_EXPOSURE,0.25);
    qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, 3);//曝光
//    qDebug() << cap.set(cv::CAP_PROP_ISO_SPEED,1000);
//    qDebug() << cap.get(cv::CAP_PROP_AUTO_EXPOSURE);
//    for(int i=0;i<42;i++)
//        qDebug() << cap.get(i);
//    qDebug() << cap.get(cv::CAP_PROP_EXPOSURE);
//    qDebug() << cap.set(cv::CAP_PROP_FPS, 2.5);

    writer = VideoWriter("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 7.4, Size(frameWidth, frameHeight));
    speed[2]='\r';
    speed[3]='\n';
    time.start();
}

void ImagProcess::refreshSerialPorts()
{
    //查找可用的串口
   foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
   {
       QSerialPort serial;
       serial.setPort(info);
       if(serial.open(QIODevice::ReadWrite))
       {
           portList.append(serial.portName());
           serial.close();
       }
   }
}

ImagProcess::~ImagProcess()
{
    m_serial->deleteLater();
    mtts << "退出";
}

void ImagProcess::openSerialPort()
{
    m_serial = new QSerialPort();
    m_serial->setBaudRate(115200);
    refreshSerialPorts();

    for (int i = 0; i < portList.size(); ++i) {
        qDebug() << "Found Port " << portList.at(i) << "Index:" << i;
        mtts << QString("串口"+portList.at(i)+"的编号为%1").arg(i);
    }
    if(portList.size()){
        qDebug() << "Input the port index: ";
        mtts << "请输入串口编号";
    }else{
        qDebug() << "Input the port index(Ports not found): ";
        mtts << "未找到串口";
    }
    int index;
    cin >> index;
    mtts.stopLast();
    if(index >= portList.size())
    {
        qDebug() << "Port not exists!";
        mtts << "串口不存在,吃枣药丸";
        return;
    }
    m_serial->setPortName(portList.at(index));
    if(!m_serial->open(QIODevice::ReadWrite)){
        qDebug() << "Port open failed!";
        mtts << "串口打开失败！哎";
    }else{
        qDebug() << "Port open succeeded!";
        mtts << ("太棒了，串口"+m_serial->portName()+"打开成功！");
    }
    qDebug() << m_serial->dataBits();
    qDebug() << m_serial->parity();
    qDebug() << m_serial->stopBits();
    qDebug() << m_serial->flowControl();
}

int ImagProcess::process()
{
    // Define Variables
    Mat src_img,gray_img;
    Mat split_img[3];
    static int lastTime = 0;
    int tempTime;
    int frameStartTime = time.elapsed();
    cap >> src_img;
//    writer << src_img;

//    qDebug() << QString("CameraCaptureTime:%1ms").arg(time.elapsed()-frameStartTime);
    tempTime = time.elapsed();

#if(1)
    // gray
    cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
    // RGB Channels
    split(src_img, split_img);

    //detect laser point
#if(1)
    int xAcc=0;
    int yAcc=0;
    double xAvg,yAvg;
    double laserPointCnt=0;
    for(int x=0;x<frameWidth;x++)
        for(int y=0;y<frameHeight;y++)
        {
            if(split_img[2].at<uchar>(Point(x,y))>thLaser)
            {
//                cv::circle(src_img, Point(x,y), 1, cv::Scalar(0,255,0), 2); //画激光点
                xAcc+=x;
                yAcc+=y;
                laserPointCnt++;
            }
        }
    if(startMove)
    {
        cv::line(src_img,Point(xTarget,0),Point(xTarget,frameHeight-1),cv::Scalar(255,0,0),2,LINE_8);
        cv::line(src_img,Point(0,yTarget),Point(frameWidth-1,yTarget),cv::Scalar(255,0,0),2,LINE_8);
    }
    else
    {
        double movAvgX1,movAvgY1;
        double movAvgX2,movAvgY2;
        static const int showAvgLen=10;
        movAvgX1=dataAverage(recordX1,showAvgLen);
        movAvgY1=dataAverage(recordY1,showAvgLen);
        movAvgX2=dataAverage(recordX2,showAvgLen);
        movAvgY2=dataAverage(recordY2,showAvgLen);
        cv::line(src_img,Point(movAvgX1,0),Point(movAvgX1,frameHeight-1),cv::Scalar(0,255,255),2,LINE_8);
        cv::line(src_img,Point(0,movAvgY1),Point(frameWidth-1,movAvgY1),cv::Scalar(0,255,255),2,LINE_8);
        cv::line(src_img,Point(movAvgX2,0),Point(movAvgX2,frameHeight-1),cv::Scalar(255,0,255),2,LINE_8);
        cv::line(src_img,Point(0,movAvgY2),Point(frameWidth-1,movAvgY2),cv::Scalar(255,0,255),2,LINE_8);
    }
    static bool firstFlag = true;
    if(startMove)
    {
        if(laserPointCnt>0)
        {
            if(firstFlag)
            {
                firstFlag=false;
                speed[0]=129;
                speed[1]=129;
                qDebug() << m_serial->write(speed);
                m_serial->flush();
            }
            xAvg=xAcc/laserPointCnt;
            yAvg=yAcc/laserPointCnt;
    //        qDebug() << QString("LaserPoint:%1,%2").arg(xAvg).arg(yAvg);
            cv::circle(src_img, Point(xAvg,yAvg), 1, cv::Scalar(255,255,0), 2); //画激光点
            if(1)
            {
                int speedSetX = 128+xTarget-xAvg;
                if(speedSetX>254)
                    speedSetX=254;
                if(speedSetX<0)
                    speedSetX=0;
                speed[0] = speedSetX;
                int speedSetY = 128+yTarget-yAvg;
                if(speedSetY>254)
                    speedSetY=254;
                if(speedSetY<0)
                    speedSetY=0;
                speed[1] = speedSetY;
                if(std::abs(xTarget-xAvg) < 10)
                {
                    static int lockDetCnt = 0;
                    lockDetCnt++;
                    if(lockDetCnt>100)
                    {
                        lockDetCnt=0;
                        mtts.stopLast();
                        mtts << QString("第%1靶打完了，现在打另一个靶").arg(curTargetNum);
                        if(std::abs(dataAverage(recordX1,20)-dataAverage(recordX2,20))<100)
                            lockTargets(1);
                        else
                            lockTargets(2);
                    }
    //                speed[0] = 255;
    //                for(int i=0;i<20;i++)
    //                {
    //                    m_serial->write(speed);
    //                }
                }
                if(m_serial->bytesAvailable()>4)
                {
                    qDebug() << m_serial->readAll();
                    m_serial->write(speed);
                    m_serial->flush();
                    qDebug() << QString("CurLoc:(%1,%2)").arg((uint8_t)speed[0]).arg((uint8_t)speed[1]);
                }
            }
        }
        else
        {
            static int laserNotFindCnt = 0;
            laserNotFindCnt++;
            if(laserNotFindCnt>30)
            {
                laserNotFindCnt=0;
                speed[0]=129;
                speed[1]=255;
                qDebug() << m_serial->write(speed);
                m_serial->flush();
                mtts << "激光点未找到";
            }
        }
    }

#endif

#endif

#if(1)

    if(startMove==false)
    {
        // medianBlur filter
        medianBlur(gray_img, gray_img, 3); //5

        // CannyDetect
//        Mat canny_img;
//        Canny(gray_img, canny_img, 12, 25, 3); //23,55 ,3
    //    qDebug() << QString("CannyRunTime:%1ms").arg(time.elapsed()-tempTime);
        tempTime = time.elapsed();

        // Hough变换检测
        finder.setDPandThreshold(1, 25); //dp,canny th
        finder.setMinVote(60); //60
        finder.setCircleParams(50, 80, 120);//min dist, minR, maxR 50,30,70
        finder.findCircles(gray_img);
        finder.drawDetectedCircles(src_img);
        recordCircle();

    //    qDebug() << QString("CircleDetTime:%1ms").arg(time.elapsed()-tempTime);
        tempTime = time.elapsed();
    }
#endif

    // Show and save the dstImage
//    imshow("Canny Output Main",canny_img);
    imshow("Raw Image", src_img);
//    imshow("BChannel", split_img[0]);
//    imshow("GChannel", split_img[1]);
//    imshow("RChannel", split_img[2]);
//    cv::setMouseCallback("RChannel",onMouse,reinterpret_cast<void*> (&split_img[2]));
//    imshow("R-BChannel", split_img[2]-split_img[0]);
    switch ((char)waitKey(1)) {
    case 'c':
        imwrite("cap.png",src_img);
        qDebug() << QString("Image saved!");
        break;
    case 'a':
        qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)+1);
        qDebug() << QString("CurrentExposeVal:%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        mtts.stopLast();
        mtts << QString("当前曝光值%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        break;
    case 's':
        qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)-1);
        qDebug() << QString("CurrentExposeVal:%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        mtts.stopLast();
        mtts << QString("当前曝光值%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        break;
    case 'w':
        qDebug() << cap.set(cv::CAP_PROP_IRIS, cap.get(cv::CAP_PROP_IRIS)+2000);
        qDebug() << QString("CurrentIRIS:%1").arg(cap.get(cv::CAP_PROP_IRIS));
        break;
    case 'x':
        qDebug() << cap.set(cv::CAP_PROP_IRIS, cap.get(cv::CAP_PROP_IRIS)-2000);
        qDebug() << QString("CurrentIRIS:%1").arg(cap.get(cv::CAP_PROP_IRIS));
        break;
    case 'r':
        qDebug() << cap.set(cv::CAP_PROP_IRIS, cap.get(cv::CAP_PROP_IRIS)+10000);
        qDebug() << QString("CurrentIRIS:%1").arg(cap.get(cv::CAP_PROP_IRIS));
        break;
    case 'v':
        qDebug() << cap.set(cv::CAP_PROP_IRIS, cap.get(cv::CAP_PROP_IRIS)-10000);
        qDebug() << QString("CurrentIRIS:%1").arg(cap.get(cv::CAP_PROP_IRIS));
        break;
    case 'q':
        qDebug() << cap.set(cv::CAP_PROP_GAIN, cap.get(cv::CAP_PROP_GAIN)+3);
        qDebug() << QString("CurrentGain:%1").arg(cap.get(cv::CAP_PROP_GAIN));
        mtts.stopLast();
        mtts << QString("当前增益%1").arg(cap.get(cv::CAP_PROP_GAIN));
        break;
    case 'z':
        qDebug() << cap.set(cv::CAP_PROP_GAIN, cap.get(cv::CAP_PROP_GAIN)-3);
        qDebug() << QString("CurrentGain:%1").arg(cap.get(cv::CAP_PROP_GAIN));
        mtts.stopLast();
        mtts << QString("当前增益%1").arg(cap.get(cv::CAP_PROP_GAIN));
        break;
    case 'p':
    {
        if(startMove==false)
        {
            startMove=true;
            firstFlag=true;
            static const int twoTargetTh = 100;
            if(std::abs(dataAverage(recordX1,20)-dataAverage(recordX2,20))<twoTargetTh)
                lockTargets(1);
            else
                lockTargets(2);
            qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)-11);
            mtts << QString("锁定成功 圆编号%1圆心坐标%2逗号%3半径%4当前曝光值%5").arg(curTargetNum).arg(xTarget).arg(yTarget).arg(r).arg(cap.get(cv::CAP_PROP_EXPOSURE));
            qDebug() << QString("圆编号%1圆心坐标%2逗号%3半径%4").arg(curTargetNum).arg(xTarget).arg(yTarget).arg(r);
            qDebug() << QString("CurrentExposeVal:%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        }
        else
        {
            startMove=false;
            qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)+11);
            mtts << QString("解除锁定 当前曝光值%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        }
        break;
    }
    case 'u':
    {
        speed[0] = speed[0] + 1;
        m_serial->write(speed);
        mtts << QString("速度%1").arg((int)speed[0]);
        break;
    }
    case 27:
        return -1;
    default:
        break;
    }

//    qDebug() << gray_img.at<uchar>(Point(100,100));

//    qDebug() << QString("TotalRunTime:%1ms").arg(time.elapsed()-frameStartTime);
//    qDebug() << QString("FrameRate:%1").arg(1000.0/(time.elapsed()-lastTime));
    if(mtts.getState()!=QTextToSpeech::Speaking)
    {
        mtts << QString("%1").arg(int(1000.0/(time.elapsed()-lastTime)));
    }

//    if(time.elapsed()-lastTime>300)
//        qDebug() << QString("FrameIntervalTime:%1ms").arg(time.elapsed()-lastTime);
    lastTime = time.elapsed();
    return 0;
}

void ImagProcess::lockTargets(int targetNum)
{
    static const int lockAvgLen=10;
    if(targetNum==1)
    {
        xTarget=dataAverage(recordX,lockAvgLen);
        yTarget=dataAverage(recordY,lockAvgLen);
        r=dataAverage(recordR,lockAvgLen);
    }
    else
    {
        if(curTargetNum==1)
        {
            curTargetNum=2;
            xTarget=dataAverage(recordX1,lockAvgLen);
            yTarget=dataAverage(recordY1,lockAvgLen);
            r=dataAverage(recordR1,lockAvgLen);
        }
        else
        {
            curTargetNum=1;
            xTarget=dataAverage(recordX2,lockAvgLen);
            yTarget=dataAverage(recordY2,lockAvgLen);
            r=dataAverage(recordR2,lockAvgLen);
        }
    }

}

void ImagProcess::recordCircle()
{
    std::vector<cv::Vec3f> circles = finder.getCenterPoints();
    std::vector<cv::Vec3f>::const_iterator itc = circles.begin();
    int i=0;
    while (itc != circles.end()) {
        addData(recordX,(*itc)[0]);
        addData(recordY,(*itc)[1]);
        addData(recordR,(*itc)[2]);

        if((*itc)[0]<dataAverage(recordX,20))
        {
            addData(recordX1,(*itc)[0]);
            addData(recordY1,(*itc)[1]);
            addData(recordR1,(*itc)[2]);
        }
        else
        {
            addData(recordX2,(*itc)[0]);
            addData(recordY2,(*itc)[1]);
            addData(recordR2,(*itc)[2]);
        }

        ++itc;
        ++i;
    }
}

double ImagProcess::dataAverage(int* recordData,int num)
{
    double avg,acc=0;
    for(int i=(RECORD_DATA_LEN-1);i>(RECORD_DATA_LEN-1-num);i--)
        acc += recordData[i];
    avg = acc / (double)num;
    return avg;
}

void ImagProcess::addData(int* recordData,int dataIn)
{
    for(int i=0;i<RECORD_DATA_LEN;i++)
        recordData[i] = recordData[i+1];
    recordData[RECORD_DATA_LEN-1] = dataIn;
}

Mat ImagProcess::ChooseROI(Mat src_img, Mat template_img, Mat midd_img)
{

    // resize images
    //resize(src_img, src_img, Size(), 0.2, 0.2);
    //resize(template_img, template_img, Size(), 0.2, 0.2);

    // match template
    int match_cols = src_img.cols - template_img.cols + 1;
    int match_rows = src_img.rows - template_img.rows + 1;

    midd_img.create(match_cols, match_rows, CV_32FC1);

    matchTemplate(src_img, template_img, midd_img, cv::TM_SQDIFF_NORMED);
    normalize(midd_img, midd_img, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal = -1;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    minMaxLoc(midd_img, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    matchLoc = minLoc;

    rectangle(src_img, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar(0, 255, 0), 2, 8, 0);
    // Chooses the input image

    Rect rect(matchLoc.x, matchLoc.y, template_img.cols, template_img.rows);

    midd_img = src_img(rect);

    return midd_img;
}

Mat ImagProcess::HoughCircle(Mat gray_img, Mat midd_img) {

    vector<Vec3f> circles;

    HoughCircles(gray_img, circles, HOUGH_GRADIENT, 1,
        1,//gray_img.rows / 16,     // change this value to detect circles with different distances to each other 16
        20, 120, 10, 200		// change the last two parameters 100, 0, 127, 138 / 100,100,400,800
                                // (min_radius & max_radius) to detect larger circles
    );

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        circle_center = Point(c[0], c[1]);
        // circle center
        // Scalar B G R
        circle(midd_img, circle_center, 1, Scalar(0, 0, 255), 3, LINE_AA);
        // circle outline
        circle_radius = c[2];
        circle(midd_img, circle_center, circle_radius, Scalar(255, 255, 0), 3, LINE_AA);

        // cout << circle_center.x << " " <<circle_center.y << " " << circle_radius << endl;
    }

    return midd_img;
}

Mat ImagProcess::HoughLine(Mat midd_img, Mat midd_line_img) {

    Mat dst_img, gray_img;

    cvtColor(midd_img, gray_img, COLOR_BGR2GRAY);

    // CannyDetect
    Canny(gray_img, midd_line_img, 30, 50, 3); //23,55 ,3
    imshow("Canny Output",midd_line_img);

    // convert cannied image to a gray one
//    cvtColor(midd_line_img, dst_img, cv::GRAY2BGR);

    // define a vector to collect all possible lines
    vector<Vec4i> mylines;
    int g_nthreshold = 39;
    HoughLinesP(midd_line_img, mylines, 1, CV_PI / 180, g_nthreshold + 1, 200, 5);

    qDebug() << mylines.size();
    // draw every line by using for
    for (size_t i = 0; i < mylines.size(); i++)
    {
        l = mylines[i];
//        if (((circle_center.x - 10) <= l[0]) && (l[0] <= (circle_center.x + 10)))
//            if (((circle_center.y - 10) <= l[1]) && (l[1] <= (circle_center.y + 10)))
//                if (((circle_center.x - circle_radius) <= l[2]) && (l[2] <= (circle_center.x + circle_radius)))
//                    if (((circle_center.y - circle_radius) <= l[3]) && (l[3] <= (circle_center.y + circle_radius)))
                    {
                        //cout << Point(l[0], l[1]) << " " << Point(l[2], l[3]) << " " << l[0] << " " << circle_center.x - circle_radius << " " << circle_center.x + circle_radius << endl;
                        // line(midd_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 2, cv::AA);
                        cho_l = l;
//                        line(midd_img, Point(circle_center.x, circle_center.y), Point(cho_l[2], cho_l[3]), Scalar(23, 180, 55), 2, LINE_AA);
                        line(midd_img,  Point(cho_l[0], cho_l[1]), Point(cho_l[2], cho_l[3]), Scalar(23, 180, 55), 2, LINE_AA);
                    }
    }

    return midd_img;
}

float ImagProcess::CalculateValue() {

    float angle = 0;
    float x, y;

    x = cho_l[2] - cho_l[0];
    y = -(cho_l[3] - cho_l[1]);

    // Angle Correction

    if (cho_l[2] > circle_center.x)
        if (cho_l[3] > circle_center.y)
            // first quadrant
            angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
        else
            // second quadrant
            angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
    else
        if (cho_l[3] < circle_center.y)
            // third quadrant
            angle = ((-3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
        else
            // fourth quadrant
            angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;

    return angle;
}


