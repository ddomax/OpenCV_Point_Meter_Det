#include "imagprocess.h"

ImagProcess::ImagProcess(QObject *parent) : QObject(parent)
{
    cap = VideoCapture(CV_CAP_DSHOW);
    cap.open(0);
    //检查摄像头是否成功打开
    if (!cap.isOpened())
    {
        qDebug()<<"摄像头未成功打开"<<endl;
    }
//    cap.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M', 'J', 'P', 'G'));
//    qDebug() << cap.get(CV_CAP_PROP_FOURCC);
//    qDebug() << cap.set(CV_CAP_PROP_FOURCC,CV_FOURCC('Y', 'U', 'Y', '2'));
//    qDebug() << cap.get(CV_CAP_PROP_FOURCC);
    qDebug() << cap.set(CV_CAP_PROP_FRAME_WIDTH, 10000); //a valid resolution set will change the format to YUY2
    qDebug() << cap.set(CV_CAP_PROP_FRAME_HEIGHT, 10000); //an invalid resolution set will use the MJPG foramt
    qDebug() << cap.set(CV_CAP_PROP_EXPOSURE, -2);//曝光
//    qDebug() << cap.set(CV_CAP_PROP_AUTO_EXPOSURE,0.25);
    qDebug() << cap.get(CV_CAP_PROP_EXPOSURE);
//    qDebug() << cap.set(CV_CAP_PROP_FPS, 2.5);
//    double grabMode,frameFormat,settings;
//    bool ok = false;
//    // Backed-specific value indicating the current capture mode.
//    grabMode = cap.get(CV_CAP_PROP_MODE);
//    qDebug() << grabMode;
//    // Format of the Mat objects returned by retrieve()
//    frameFormat = cap.get(CV_CAP_PROP_FORMAT);
//    // Some available settings
//    settings = cap.get(CV_CAP_PROP_SETTINGS);

//    // Playing around GRAB_MODE

//    // Boolean flags indicating whether images should be converted to RGB.
//    qDebug() << cap.set(CV_CAP_PROP_CONVERT_RGB, 0);
//    int i = -100;
//    while(ok == false && i<100)
//    {
//     if (i != 0)
//       ok = cap.set(CV_CAP_PROP_MODE, grabMode + i);
//     i++;
//    }
//    if(ok)
//    {
//     grabMode = cap.get(CV_CAP_PROP_MODE);
//     qDebug() << "Grab Mode=" << grabMode << " is supported" << endl;
//    }
//    grabMode = cap.get(CV_CAP_PROP_MODE);
//    qDebug() << grabMode;
    for(int i=0;i<42;i++)
        qDebug() << cap.get(i); //Show available properties
    time.start();
}

int ImagProcess::process()
{
    // Define Variables
    Mat src_img,gray_img;
    static int lastTime = 0;
    int tempTime;
    int frameStartTime = time.elapsed();
    cap >> src_img;

//    qDebug() << QString("CameraCaptureTime:%1ms").arg(time.elapsed()-frameStartTime);
    tempTime = time.elapsed();

#if(1)
    // gray
    cvtColor(src_img, gray_img, COLOR_BGR2GRAY);

    // medianBlur filter
    medianBlur(gray_img, gray_img, 3); //5

    // CannyDetect
    Mat canny_img;
    Canny(gray_img, canny_img, 12, 25, 3); //23,55 ,3
    imshow("Canny Output Main",canny_img);

//    qDebug() << QString("CannyRunTime:%1ms").arg(time.elapsed()-tempTime);
#endif

    // Show and save the dstImage
    imshow("Canny Output Main",canny_img);
    imshow("Raw Image", src_img);

    // Key Switch
    switch ((char)waitKey(1)) {
    case 'c':
        imwrite("cap.png",src_img);
        qDebug() << QString("Image saved!");
        break;
    case 'a':
        qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)+1);
        qDebug() << QString("CurrentExposeVal:%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
        break;
    case 's':
        qDebug() << cap.set(cv::CAP_PROP_EXPOSURE, cap.get(cv::CAP_PROP_EXPOSURE)-1);
        qDebug() << QString("CurrentExposeVal:%1").arg(cap.get(cv::CAP_PROP_EXPOSURE));
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
        break;
    case 'z':
        qDebug() << cap.set(cv::CAP_PROP_GAIN, cap.get(cv::CAP_PROP_GAIN)-3);
        qDebug() << QString("CurrentGain:%1").arg(cap.get(cv::CAP_PROP_GAIN));
        break;
    case 27:
        return -1;
    default:
        break;
    }

//    qDebug() << QString("TotalRunTime:%1ms").arg(time.elapsed()-frameStartTime);
    qDebug() << QString("FrameRate:%1").arg(1000.0/(time.elapsed()-lastTime));
    if(time.elapsed()-lastTime>200)
        qDebug() << QString("FrameIntervalTime:%1ms").arg(time.elapsed()-lastTime);
    lastTime = time.elapsed();
    return 0;
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

    matchTemplate(src_img, template_img, midd_img, CV_TM_SQDIFF_NORMED);
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
    Canny(gray_img, midd_line_img, 30, 70, 3); //23,55 ,3
    imshow("Canny Output",midd_line_img);

    // convert cannied image to a gray one
//    cvtColor(midd_line_img, dst_img, CV_GRAY2BGR);

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
                        // line(midd_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 2, CV_AA);
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


