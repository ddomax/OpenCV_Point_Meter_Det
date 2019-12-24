//// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//
////#include "opencv2/cv.hpp"
//#include "opencv2/opencv.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <string>
//#include <stack>
//using namespace cv;
//using namespace std;
//
//typedef uchar BYTE;
//
//void imgreverse(Mat srcImg, Mat outImg, int w, int h);
//void thresholdImg(Mat inputImg, Mat outImg, BYTE thr, int w, int h);
//void HilditchThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void ZhangFastThin(BYTE* inputimg, BYTE* outImg, int w, int h);
//void PavlidisThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void RosenfeldThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void BasedIndexTableThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void MorphologyThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void MorphologySharp(BYTE* inputImg, BYTE* outImg, int w, int h);
//int main()
//{
//	Mat pImageBuffer;
//	pImageBuffer = imread("11.jpg", 1);
//
//	//�Ҷ�ͼ��
//	Mat srcImg;
//	srcImg.create(pImageBuffer.size(), CV_8UC1);
//	cvtColor(pImageBuffer, srcImg, CV_BGR2GRAY);
//
//	int w = srcImg.cols;
//	int h = srcImg.rows;
//	int n = w * h;
//
//	//��תͼ��
//	//imgreverse(srcImg, srcImg,w,h);
//
//	//��ֵ��ͼ��
//	thresholdImg(srcImg, srcImg, 50, w, h);
//
//	//��ϸ��ͼ��
//	BYTE* inputImg = new BYTE[n];
//	memcpy(inputImg, srcImg.data, n);
//
//	//��ʾͼ��
//	Mat imgshow;
//	imgshow.create(srcImg.size(), srcImg.type());
//
//
//	//Zhang���п����㷨
//	BYTE* ZhangFastImg = new BYTE[n];
//	ZhangFastThin(inputImg, ZhangFastImg, w, h);
//	memcpy(imgshow.data, ZhangFastImg, n);
//	imshow("ZhangFast...", imgshow);
//	delete[] ZhangFastImg;
//
//	//Hilditch�㷨
//	BYTE* HilditchImg = new BYTE[n];
//	HilditchThin(inputImg, HilditchImg, w, h);
//	memcpy(imgshow.data, HilditchImg, n);
//	imshow("Hilditch...", imgshow);
//	delete[] HilditchImg;
//
//
//	//Pavlidis�㷨
//	BYTE* PavlidisImg = new BYTE[n];
//	PavlidisThin(inputImg, PavlidisImg, w, h);
//	memcpy(imgshow.data, PavlidisImg, n);
//	imshow("Pavlidis...", imgshow);
//	delete[] PavlidisImg;
//
//	//Rosenfeld�㷨
//	BYTE* RosenfeldImg = new BYTE[n];
//	RosenfeldThin(inputImg, RosenfeldImg, w, h);
//	memcpy(imgshow.data, RosenfeldImg, n);
//	imshow("Rosenfeld...", imgshow);
//	delete[] RosenfeldImg;
//
//	//BasedIndexTableThin�㷨
//	BYTE* BasedIndexTableImg = new BYTE[n];
//	BasedIndexTableThin(inputImg, BasedIndexTableImg, w, h);
//	memcpy(imgshow.data, BasedIndexTableImg, n);
//	imshow("BasedIndexTable...", imgshow);
//	delete[] BasedIndexTableImg;
//
//
//	//MorphologyThin�㷨
//	BYTE* MorphologyImg = new BYTE[n];
//	MorphologyThin(inputImg, MorphologyImg, w, h);
//	memcpy(imgshow.data, MorphologyImg, n);
//	imshow("Morphology...", imgshow);
//	delete[] MorphologyImg;
//
//
//	//ɾ����̬������ڴ�
//	delete[] inputImg;
//
//	waitKey(0);
//	return 0;
//}
//
////ͼ��ת
//void imgreverse(Mat srcImg, Mat outImg, int w, int h)
//{
//	double sum = 0;
//	for (int i = 0; i < h; i++)
//	{
//		uchar* pin = srcImg.ptr<uchar>(i);
//		for (int j = 0; j <w; j++)
//		{
//			sum += pin[j];
//		}
//	}
//
//	double avr = sum / (w*h);
//
//	if (avr > 128)
//	{
//		for (int i = 0; i < h; i++)
//		{
//			uchar* pin = srcImg.ptr<uchar>(i);
//			uchar* pout = outImg.ptr<uchar>(i);
//			for (int j = 0; j <w; j++)
//			{
//				pout[j] = 255 - pin[j];
//
//			}
//		}
//	}
//
//}
//
////��ֵ�ָ��ֵ��ͼ��
//void thresholdImg(Mat inputImg, Mat outImg, BYTE thr, int w, int h)
//{
//	for (int i = 0; i<h; ++i)
//	{
//		BYTE* pin = inputImg.ptr<BYTE>(i);
//		BYTE* pout = outImg.ptr<BYTE>(i);
//		for (int j = 0; j < w; ++j)
//		{
//			if (pin[j] >= thr)
//				pout[j] = 1;
//			else
//				pout[j] = 0;
//
//		}
//	}
//}
//
////Zhang���п���ϸ���㷨
//void ZhangFastThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE foreground = 1; //ǰ����
//	BYTE background = 1 - foreground;//������
//
//									 //8�������
//									 //p3  p2  p1
//									 //p4   p   p0
//									 //p5  p6  p7
//	static int d[8] = { 1, 1 - w, -w, -1 - w, -1, w - 1, w, w + 1 };
//
//	bool bOdd = true;
//	bool bDel = true;
//	bool *mask = new bool[sizen];
//	memset(mask, 0, sizen);
//
//	while (bDel || bOdd)
//	{
//		bDel = false;
//		for (int i = 1; i < h - 1; i++)
//			for (int j = 1; j < w - 1; j++)
//			{
//				int k = i * w + j;
//
//				//����1��p������ǰ����
//				if (outImg[k] != foreground) continue;
//
//				//����2��2 <= N(p) <= 6
//				int np = 0;
//				for (int i = 0; i < 8; i++)
//					if (outImg[k + d[i]] != foreground) np++;
//				if (np < 2 || 6 < np) continue;
//
//				//����3��S(p) = 1
//				int sp = 0;
//				for (int i = 0; i < 8; i++)
//					if (outImg[k + d[i & 7]] != foreground && outImg[k + d[(i + 1) & 7]] != background) sp++;
//				if (sp != 1) continue;
//
//				if (bOdd)
//				{
//					//����4��p2*p0*p6 = 0
//					if (outImg[k + d[2]] != background && outImg[k + d[0]] != background && outImg[k + d[6]] != background) continue;
//					//����5��p0*p6*p4 = 0
//					if (outImg[k + d[0]] != background && outImg[k + d[6]] != background && outImg[k + d[4]] != background) continue;
//				}
//				else
//				{
//					//����4��p6*p4*p2==0
//					if (outImg[k + d[6]] != background && outImg[k + d[4]] != background && outImg[k + d[2]] != background) continue;
//					//����5��p4*p2*p0==0
//					if (outImg[k + d[4]] != background && outImg[k + d[2]] != background && outImg[k + d[0]] != background) continue;
//				}
//				bDel = true;
//				mask[k] = true; //���ɾ��
//			}
//
//		bOdd = !bOdd;
//		if (!bDel) continue;
//		//�����ɾ���ĵ���Ϊ����ɫ
//		for (int i = 0; i < sizen; ++i)
//		{
//			if (mask[i])
//				outImg[i] = background;
//		}
//	}
//
//	delete[] mask;
//
//	for (int i = 0; i < sizen; i++) outImg[i] *= 255;
//}
//
////Pavlidisͼ��ϸ���㷨
//void FillNeighbor8(BYTE* p, BYTE* list, int w)
//{
//	list[0] = p[1];
//	list[1] = p[-w + 1];
//	list[2] = p[-w];
//	list[3] = p[-w - 1];
//	list[4] = p[-1];
//	list[5] = p[w - 1];
//	list[6] = p[w];
//	list[7] = p[w + 1];
//}
//void PavlidisThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	//8�������
//	//p3  p2  p1
//	//p4   p   p0
//	//p5  p6  p7
//	BYTE  list[8];
//
//	//ͼ��߿�����ֵΪ0
//	for (int i = 0; i< h; i++)
//		for (int j = 0; j<w; j++)
//		{
//			int ij = i * w + j;
//
//			if (i == 0 || i == (h - 1) || j == 0 || j == (w - 1))
//				outImg[ij] = 0;
//		}
//
//	BYTE bdr1, bdr2, bdr4, bdr5;
//	int   b;
//
//	//ѭ����־
//	bool loop = true;
//
//	while (loop)
//	{
//		BYTE* img = outImg;
//		//��һ��ѭ����ȡ��ǰ��������������2��ʾ
//		for (int i = 1; i< h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j < w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] != 1)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				//bdr1��2���Ʊ�ʾ��p0...p6p7���У�10000011,p0=1,p6=p7=1
//				bdr1 = 0;
//				for (int k = 0; k<8; k++)
//				{
//					if (list[k] >= 1)
//						bdr1 |= 0x80 >> k;
//				}
//
//				//�ڲ���;p0, p2, p4, p6����Ϊ1, �Ǳ߽�㣬���Լ���ѭ��
//				//0xaa
//				//  0   1   0   
//				//  1         1
//				//  0   1    0
//				if ((bdr1 & 0xaa) == 0xaa)
//					continue;
//
//				//�����ڲ��㣬���Ǳ߽��(����), ���Ϊ2
//				p[0] = 2;
//
//				b = 0;
//
//				for (int k = 0; k <= 7; k++)
//				{
//					b += bdr1 & (0x80 >> k);
//				}
//				//�ڱ߽���У�����1�����Ƕ˵㣬����0�����ǹ����㣬��ʱ���3
//				if (b <= 1)
//					p[0] = 3;
//
//				//������˵��p�����м�㣬��ȥ���������
//				// 0x70        0x7         0x88      0xc1        0x1c      0x22      0x82     0x1      0xa0     0x40     0x28    0x10       0xa      0x4
//				// 0 0 0     0  1  1     1  0   0    0   0   0    1  1  0    0   0   1  0  0  1  0 0 0    0  0  0   0 0 0    1  0  0   0  0  0  1  0  1   0 1 0
//				// 1    0     0      1     0       0    0        1    1      0    0        0  0      0  0    1    0      0   0    0    0      0   1      0  0     0    0    0
//				// 1 1 0     0  0  0     0  0   1    0   1   1    0  0  0    1   0   1  0  0  1  0 0 0    1  0  1   0 1 0    1  0  0   0  0  0  0  0  0   0 0 0
//				if ((bdr1 & 0x70) != 0 && (bdr1 & 0x7) != 0 && (bdr1 & 0x88) == 0)
//					p[0] = 3;
//				else if ((bdr1 && 0xc1) != 0 && (bdr1 & 0x1c) != 0 && (bdr1 & 0x22) == 0)
//					p[0] = 3;
//				else if ((bdr1 & 0x82) == 0 && (bdr1 & 0x1) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0xa0) == 0 && (bdr1 & 0x40) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0x28) == 0 && (bdr1 & 0x10) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0xa) == 0 && (bdr1 & 0x4) != 0)
//					p[0] = 3;
//			}
//		}
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] == 0)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				bdr1 = bdr2 = 0;
//
//				//bdr1��2���Ʊ�ʾ�ĵ�ǰ��p��8������ͨ�����hdr2�ǵ�ǰ����Χ��������������
//				for (int k = 0; k <= 7; k++)
//				{
//					if (list[k] >= 1)
//						bdr1 |= 0x80 >> k;
//					if (list[k] >= 2)
//						bdr2 |= 0x80 >> k;
//				}
//
//				//��ȣ���Χȫ��ֵΪ2�����أ�����
//				if (bdr1 == bdr2)
//				{
//					p[0] = 4;
//					continue;
//				}
//
//				//p0��Ϊ2������
//				if (p[0] != 2) continue;
//				//=4���ǲ���ɾ����������
//				//     0x80       0xa     0x40        0x1      0x30   0x6
//				//   0 0 0      1  0 1    0  0  0    0  0  0   0 0 0   0 1 1
//				//   0    0      0     0    0      0    0      1   1    0   0    0
//				//   0 0 1      0  0 0    0  1  0    0  0  0   1 0 0   0 0 0
//
//				if ((bdr2 & 0x80) != 0 && (bdr1 & 0xa) == 0 &&
//					(((bdr1 & 0x40) != 0 || (bdr1 & 0x1) != 0) && (bdr1 & 0x30) != 0 && (bdr1 & 0x6) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x20) != 0 && (bdr1 & 0x2) == 0 &&
//					(((bdr1 & 0x10) != 0 || (bdr1 & 0x40) != 0) && (bdr1 & 0xc) != 0 && (bdr1 & 0x81) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x8) != 0 && (bdr1 & 0x80) == 0 &&
//					(((bdr1 & 0x4) != 0 || (bdr1 & 0x10) != 0) && (bdr1 & 0x3) != 0 && (bdr1 & 0x60) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x2) != 0 && (bdr1 & 0x20) == 0 &&
//					(((bdr1 & 0x1) != 0 || (bdr1 & 0x4) != 0) && (bdr1 & 0xc0) != 0 && (bdr1 & 0x18) != 0))
//				{
//					p[0] = 4;
//				}
//			}
//		}
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] != 2)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				bdr4 = bdr5 = 0;
//				for (int k = 0; k <= 7; k++)
//				{
//					if (list[k] >= 4)
//						bdr4 |= 0x80 >> k;
//					if (list[k] >= 5)
//						bdr5 |= 0x80 >> k;
//				}
//				//ֵΪ4��5������
//				if ((bdr4 & 0x8) == 0)
//				{
//					p[0] = 5;
//					continue;
//				}
//				if ((bdr4 & 0x20) == 0 && bdr5 == 0)
//				{
//					p[0] = 5;
//					continue;
//				}
//
//			}
//		}
//
//		loop = false;
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//				if (p[0] == 2 || p[0] == 5)
//				{
//					loop = true;
//					p[0] = 0;
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
////Rosenfeldͼ��ϸ���㷨
//void RosenfeldThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE* tempImg = new BYTE[sizen];
//	memcpy(tempImg, inputImg, sizen);
//
//	//8�������
//	//p3  p2  p1
//	//p4   p   p0
//	//p5  p6  p7
//	BYTE list[8];
//
//	int a[5] = { 0, -1, 1, 0, 0 };
//	int b[5] = { 0, 0, 0, 1, -1 };
//
//	BYTE  cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
//
//	//ѭ����־
//	bool  loop = true;
//
//	while (loop)
//	{
//		loop = false;
//
//		for (int k = 1; k <= 4; k++)
//		{
//			for (int i = 1; i<h - 1; i++)
//			{
//				int ii = i + a[k];
//
//				for (int j = 1; j<w - 1; j++)
//				{
//					int ij = i * w + j;
//					BYTE* pos = outImg + ij;
//
//					if (!outImg[ij])
//						continue;
//
//					int jj = j + b[k];
//					int kk1 = ii * w + jj;
//
//					if (outImg[kk1])
//						continue;
//
//					FillNeighbor8(pos, list, w);
//
//					int nrnd = 0;
//					for (int k = 0; k < 8; k++)
//						nrnd += list[k];
//
//					if (nrnd <= 1)
//						continue;
//
//					cond = 0;
//					n48 = list[3] + list[7];
//					n26 = list[1] + list[5];
//					n24 = list[1] + list[3];
//					n46 = list[3] + list[5];
//					n68 = list[5] + list[7];
//					n82 = list[7] + list[1];
//					n123 = list[0] + list[1] + list[2];
//					n345 = list[2] + list[3] + list[4];
//					n567 = list[4] + list[5] + list[6];
//					n781 = list[6] + list[7] + list[0];
//
//					if (list[1] == 1 && n48 == 0 && n567>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[5] == 1 && n48 == 0 && n123>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[7] == 1 && n26 == 0 && n345>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[3] == 1 && n26 == 0 && n781>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[4] == 1 && n46 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[6] == 1 && n68 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[0] == 1 && n82 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[2] == 1 && n24 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					cond = 1;
//
//					tempImg[ij] = 0;
//
//					loop = true;
//				}
//			}
//
//			memcpy(outImg, tempImg, sizen);
//		}
//	}
//
//	delete[] tempImg;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
////BasedIndexTableͼ��ϸ���㷨
//void BasedIndexTableThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	BYTE deletemark[256] = {
//		0,0,0,0,0,0,0,1,    0,0,1,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,1,1,1,0,1,1,
//		0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
//		0,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
//		1,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
//		0,0,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,1,0,0,1,1,
//		1,1,0,1,0,0,0,1,    0,0,0,0,0,0,0,0,
//		1,1,0,1,0,0,0,1,    1,1,0,0,1,0,0,0,
//		0,1,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,1,1,1,
//		1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0,
//		1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0
//	};//IndexTable��������ʾĳ��Ԫ��8�����256�������1ɾ����0��ɾ��
//
//	int sizen = w * h;
//	BYTE* tempImg = new BYTE[sizen];
//	memset(tempImg, 0, sizen);
//
//	//8�������
//	//p0  p1  p2
//	//p7   p   p3
//	//p6  p5  p4
//	BYTE list[8];
//
//	BYTE foreground = 1;//ǰ����
//	BYTE background = 1 - foreground;//������
//
//									 //ѭ����־
//	bool loop = true;
//
//	while (loop)
//	{
//		loop = false;
//
//		memset(tempImg, 0, sizen);
//
//		//�������Ե��(����)
//		BYTE* pmid = inputImg + w + 1;
//		BYTE* pmidtemp = tempImg + w + 1;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				if (*pmid == background)//0��������
//				{
//					pmid++;
//					pmidtemp++;
//					continue;
//				}
//
//				FillNeighbor8(pmid, list, w);
//
//				BYTE sum = 1;
//				for (int k = 0; k < 8; k++)
//					sum &= list[k];
//
//				if (sum == 0)
//				{
//					*pmidtemp = foreground;//��Ե
//				}
//
//				pmid++;
//				pmidtemp++;
//			}
//
//			//�ƶ�����һ�еĵ�2���㿪ʼ
//			pmid = pmid + 2;
//			pmidtemp = pmidtemp + 2;
//		}
//
//		//����ɾ��
//		pmid = inputImg + w + 1;
//		pmidtemp = tempImg + w + 1;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				if (*pmidtemp == background)//1-��Ե��0-�м��
//				{
//					pmid++;
//					pmidtemp++;
//					continue;
//				}
//
//				FillNeighbor8(pmid, list, w);
//
//				list[2] *= 2;
//				list[1] *= 4;
//				list[0] *= 8;
//				list[7] *= 16;
//				list[6] *= 32;
//				list[5] *= 64;
//				list[4] *= 128;
//
//				BYTE sum = 0;
//				for (int k = 0; k < 8; k++)
//					sum |= list[k];
//
//				if (deletemark[sum] == 1)
//				{
//					*pmid = background;
//					loop = true; //����ɨ�������ϸ��
//				}
//
//				pmid++;
//				pmidtemp++;
//			}
//
//			//�ƶ�����һ�еĵ�2���㿪ʼ
//			pmid = pmid + 2;
//			pmidtemp = pmidtemp + 2;
//		}
//	}
//
//	delete[] tempImg;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] = 255 * inputImg[i];
//}
////Morphologyϸ���㷨
//void MorphologyThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	//inputImg:�����ͼ��
//	//img2: ����ͼ��Ŀ���
//	//img3:erode���ͼ��
//	//img4:open�������м�ֵ
//	//img5:erode-open���ͼ��
//	//img6:������ͼ��
//	//outImg:�����ͼ��
//
//	int n = w * h;
//	BYTE* img2 = new BYTE[n];
//	BYTE* img3 = new BYTE[n];
//	BYTE* img4 = new BYTE[n];
//	BYTE* img5 = new BYTE[n];
//	BYTE* img6 = new BYTE[n];
//
//	memcpy(img2, inputImg, n);
//	memset(outImg, 0, n);
//
//	//loop flag
//	bool flag = true;
//	//erode flag
//	bool flag2 = true;
//
//	while (flag)
//	{
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img3[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//
//							if (img2[r*w + j] != 1)
//								flag2 = false;
//						}
//				}
//
//				if (flag2)
//					img3[ij] = 1;
//				else
//					img3[ij] = 0;
//			}//img3 end
//
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img4[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//							if (img3[r*w + s] != 1)
//								flag2 = false;
//						}
//
//					if (flag2)
//						img4[ij] = 1;
//					else
//						img4[ij] = 0;
//				}
//			}//img4 end
//
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img5[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//							if (img4[r*w + s] != 1)
//								flag2 = false;
//						}
//
//					if (flag2)
//						img5[ij] = 1;
//					else
//						img5[ij] = 0;
//				}
//			}//img5 end
//
//			 //����,��ͬ��subtract����
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				img6[ij] = img3[ij] - img5[ij];
//			}//img6 end
//
//			 //������
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (img6[ij] == 1)
//					outImg[ij] = 1;
//			}//img6 end
//
//		memcpy(img2, img3, n);
//
//		//�ж�ѭ����־
//		flag = false;
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (img2[ij] == 1)
//					flag = true;
//			}//img6 end
//
//	}
//
//	for (int i = 0; i < n; i++)
//		outImg[i] *= 255;
//
//
//	delete[] img2;
//	delete[] img3;
//	delete[] img4;
//	delete[] img5;
//	delete[] img6;
//}
//
////Hilditch2ͼ��ϸ���㷨
//int  DetectConnectivity(int* list)
//{
//	int count = list[6] - list[6] * list[7] * list[0];
//	count += list[0] - list[0] * list[1] * list[2];
//	count += list[2] - list[2] * list[3] * list[4];
//	count += list[4] - list[4] * list[5] * list[6];
//	return count;
//}
//void FillNeighbors(BYTE* p, int* list, int width, BYTE foreground)
//{
//	// list �洢���ǲ�������ǰ����Ϊ0��������Ϊ1���Է����������ļ��� 
//
//	list[0] = p[1] == foreground ? 0 : 1;
//	list[1] = p[1 - width] == foreground ? 0 : 1;
//	list[2] = p[-width] == foreground ? 0 : 1;
//	list[3] = p[-1 - width] == foreground ? 0 : 1;
//	list[4] = p[-1] == foreground ? 0 : 1;
//	list[5] = p[-1 + width] == foreground ? 0 : 1;
//	list[6] = p[width] == foreground ? 0 : 1;
//	list[7] = p[1 + width] == foreground ? 0 : 1;
//}
//void HilditchThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE foreground = 1;//ǰ����Ϊ1
//	BYTE background = 1 - foreground;//������Ϊ0
//
//	bool* mask = new bool[sizen];
//	memset(mask, 0, sizen);
//
//	//8�������
//	//  p3  p2  p1 
//	//  p4   p   p0 
//	//  p5  p6  p7 
//	int* list = new int[8];
//
//	bool loop = true;//ѭ����־
//
//	while (loop)
//	{
//		loop = false;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				BYTE* p = outImg + i * w + j;
//
//				// ����1��p ������ǰ���� 
//				if (*p != foreground) continue;
//
//				// list �洢����
//				FillNeighbors(p, list, w, foreground);
//
//				// ����2��p0,p2,p4,p6 ����Ϊǰ���� 
//				if (list[0] == 0 && list[2] == 0 && list[4] == 0 && list[6] == 0)
//					continue;
//
//				// ����3: p0~p7����������ǰ���� 
//				int count = 0;
//				for (int i = 0; i < 8; i++)
//				{
//					count += list[i];
//				}
//
//				if (count > 6) continue;
//
//				// ����4������������1 
//				if (DetectConnectivity(list) != 1) continue;
//
//				// ����5: ����p2�ѱ��ɾ��������p2Ϊ���������ı�p�������� 
//				if (mask[(i - 1)*w + j])
//				{
//					list[2] = 1;
//					if (DetectConnectivity(list) != 1)
//						continue;
//					list[2] = 0;
//				}
//
//				// ����6: ����p4�ѱ��ɾ��������p4Ϊ���������ı�p�������� 
//				if (mask[i*w + j - 1])
//				{
//					list[4] = 1;
//					if (DetectConnectivity(list) != 1)
//						continue;
//				}
//				mask[i*w + j] = 1; // ���ɾ�� 
//				loop = true;
//			}
//		}
//
//		//������ɾ��������Ԫ��0
//		for (int i = 0; i < sizen; i++)
//		{
//			if (mask[i])
//			{
//				outImg[i] = background;
//			}
//		}
//	}
//
//	delete[] list;
//	delete[] mask;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
//
//
////��̬ѧ��Ե
//void FillNeighbor9(BYTE* p, BYTE* list, int w)
//{
//
//	list[0] = p[1];
//	list[1] = p[-w + 1];
//	list[2] = p[-w];
//	list[3] = p[-w - 1];
//	list[4] = p[-1];
//	list[5] = p[w - 1];
//	list[6] = p[w];
//	list[7] = p[w + 1];
//	list[8] = p[0];
//}
//void MorphologySharp(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE* tempImg = new BYTE[sizen];
//	memcpy(tempImg, inputImg, sizen);
//
//	//�������
//	BYTE list[9];
//
//	BYTE* pt = tempImg;
//	BYTE* po = outImg;
//	for (int i = 1; i<h - 1; i++)
//	{
//		for (int j = 1; j < w - 1; j++)
//		{
//			po = outImg + i * w + j;
//			pt = tempImg + i * w + j;
//			FillNeighbor9(pt, list, w);
//
//			BYTE min = 255;
//			for (int k = 0; k<9; k++)
//			{
//				min = (min >= list[k] ? list[k] : min);
//			}
//
//			(*po) = min;
//		}
//	}
//
//	//2*ԭͼ-��ʴ=��
//	for (int i = 0; i< sizen; i++)
//		outImg[i] = (BYTE)(2 * inputImg[i] - outImg[i]);
//
//	delete[] tempImg;
//}
//
