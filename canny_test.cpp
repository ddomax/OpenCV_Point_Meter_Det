//#include <opencv2/opencv.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//
//using namespace std;
//using namespace cv;
//
//
//Mat g_srcImage, g_dstImage, g_midImage;//ԭʼͼ���м�ͼ��Ч��ͼ  
//vector<Vec4i> g_lines;//����һ��ʸ���ṹg_lines���ڴ�ŵõ����߶�ʸ������  
//					  //�������յ�TrackBarλ�ò���  
//int g_nthreshold = 100;
//
//static void showImage1(int, void*);
//static void showImage2(int, void*);
//int thred1 = 23;
//int thred2 = 55;
//// 23 55
//int main()
//{
//	//����ԭʼͼ��Mat��������     
//	g_srcImage = imread("12.jpg", 0);
//	//��ʾԭʼͼ    
//	imshow("Origin Image", g_srcImage);
//	//����������  
//	namedWindow("Dst Image", 1);
//
//	createTrackbar("��ֵ1", "Dst Image", &thred1, 200, showImage1);
//	createTrackbar("��ֵ2", "Dst Image", &thred2, 200, showImage2);
//	//���б�Ե����ת��Ϊ�Ҷ�ͼ  
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//����һ��canny��Ե���  
//	cvtColor(g_midImage, g_dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ  
//												  //����һ�λص�����������һ��HoughLinesP����  
//	showImage1(thred1, 0);
//	showImage2(thred2, 0);
//	//��ʾЧ��ͼ    
//	imshow("Dst Image", g_dstImage);
//	waitKey(0);
//	return 0;
//}
//
//static void showImage1(int thred1, void*) {
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//����һ��canny��Ե���  
//	imshow("Dst Image", g_midImage);
//}
//
//static void showImage2(int thred2, void*) {
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//����һ��canny��Ե���  
//	imshow("Dst Image", g_midImage);
//}