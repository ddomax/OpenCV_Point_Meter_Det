#ifndef CIRCLEFINDER_H
#define CIRCLEFINDER_H
#include <omp.h>
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <QDebug>
 
class CircleFinder{
private:
	std::vector<cv::Vec3f> circles;
	double dp;       // 累加器的分辨率(图像尺寸/2)
	double minDist;  // 两个圆之间的最小距离
	double th;       // Canny中的高阈值
	double minVote;  // 最小投票数
	int minR;
	int maxR;        // 有效半径的最小值和最大值
public:
	CircleFinder() {
		dp = 1.0, minDist = 1.0;
		th = 300;
		minVote = 80;
		minR = 1, maxR = 100;
	}
    void setDPandThreshold(double i_dp, double i_th) {
        dp = i_dp;
        th = i_th;
	}
	void setMinVote(double minv) {
		minVote = minv;
	}
    void setCircleParams(double minD, int i_minR, int i_maxR) {
		minDist = minD;
        minR = i_minR;
        maxR = i_maxR;
	}
 
	// Hough变换检测圆
	void findCircles(cv::Mat& imageBlur) {
		circles.clear();
        cv::HoughCircles(imageBlur, circles, cv::HOUGH_GRADIENT, dp, minDist, th, minVote, minR, maxR);
	}
 
	void drawDetectedCircles(cv::Mat &image, cv::Scalar color = cv::Scalar(255)) {
		std::vector<cv::Vec3f>::const_iterator itc = circles.begin();
		while (itc != circles.end()) {
			cv::Point pt((*itc)[0], (*itc)[1]);
            cv::circle(image, pt, int((*itc)[2]), cv::Scalar(255), 2); //画圆
            cv::circle(image, pt, 1, cv::Scalar(0,0,255), 2); //画圆心点
//            qDebug() << int((*itc)[2]);
			++itc;
		}
	}

    const std::vector<cv::Vec3f> getCenterPoints()
    {
        return circles;
    }
};

#endif //CIRCLEFINDER_H
