#include "DIBR.h" 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp> 
#include<iostream>
using namespace std;
using namespace cv;
void DIBR(IplImage *color,IplImage *depth,IplImage *dibr_n)
{ 
	cvSmooth(depth, depth, CV_GAUSSIAN, 3, 0, 0, 0);
	IplImage *gray_b,*gray_g,*gray_r; 
	IplImage *dibr_b,*dibr_g,*dibr_r; 
	gray_b=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1); 
	gray_g=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1); 
	gray_r=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1); 

	dibr_b=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1); 
	cvSetZero(dibr_b);
	dibr_g=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1);  
	cvSetZero(dibr_g);
	dibr_r=cvCreateImage(cvGetSize(depth),IPL_DEPTH_8U,1);
	cvSetZero(dibr_r);
	cvSplit(color,gray_b,gray_g,gray_r,NULL);   

	double table[256];  
	int knear = 0; 
	int kfar = 128; 
	int xb = 6; // —€º‰æ‡
	int D = 800; // ŒÔÃÂæ‡À´—€æ‡¿Î
	int Npix = 720; 
	for (int i = 0; i < 256; i++)  
	{ 
		double A = i * ( knear/64 + kfar/16 ) / 255; 
		double h = - xb * Npix * ( A-kfar/16) / D; 
		table[i] = h/2; 
	} 
	int S = 25; // depth=0 ◊Ó¥Û∆´“∆
	int step = depth->widthStep;///sizeof(uchar); 
	uchar* datadepth = (uchar*)depth->imageData; 
	uchar* datagray_b = (uchar*)gray_b->imageData; 
	uchar* datagray_g = (uchar*)gray_g->imageData; 
	uchar* datagray_r = (uchar*)gray_r->imageData; 
	uchar* datadibr_b = (uchar*)dibr_b->imageData;  
	uchar* datadibr_g = (uchar*)dibr_g->imageData; 
	uchar* datadibr_r = (uchar*)dibr_r->imageData; 

	//”“
	for (int i=0; i<depth->height;i++) 
	{ 
		for (int j=0; j<depth->width; j++) 
		{ 
			int d = (int)(datadepth[i*step+j]); 
			int shift = table[d]; 
			if (j+shift-S>=0) 
			{ 
				datadibr_b[i*step+j+shift-S] = datagray_b[i*step+j]; 
			}   
		} 
	} 
	for (int i=0; i<depth->height;i++) 
	{ 
		for (int j=0; j<depth->width; j++) 
		{ 
			int d = (int)(datadepth[i*step+j]); 
			int shift = table[d]; 
			if (j+shift-S>=0) 
			{ 
				datadibr_g[i*step+j+shift-S] = datagray_g[i*step+j]; 
			} 
		}  
	} 
	for (int i=0; i<depth->height;i++)
	{ 
		for (int j=0; j<depth->width; j++) 
		{ 
			int d = (int)(datadepth[i*step+j]); 
			int shift = table[d]; 
			if (j+shift-S>=0) 
			{ 
				datadibr_r[i*step+j+shift-S] = datagray_r[i*step+j]; 
			} 
		} 
	} 
	cvMerge(dibr_b, dibr_g, dibr_r, NULL, dibr_n);
	CvScalar s;
	CvScalar up;
	for (int i = 0; i < dibr_n->height; i++)
	{
		for (int j = 1; j < dibr_n->width; j++)
		{
			s = cvGet2D(dibr_n, i, j);
			up = cvGet2D(dibr_n, i, j - 1);
			//cout << s.val[0] << "B" << s.val[1] << "G" << s.val[2] << endl;
			if (s.val[0] == 0 && s.val[1] == 0 && s.val[2] == 0)
			{
				
				s.val[0] = up.val[0];
				s.val[1] = up.val[1];
				s.val[2] = up.val[2];
				cvSet2D(dibr_n, i, j, s);
			}
		}
	}
	//cvMerge(dibr_b,dibr_g,dibr_r,NULL,dibr_n); 
} 