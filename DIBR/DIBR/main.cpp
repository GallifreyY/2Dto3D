#include "opencv2/opencv.hpp" 
#include "DIBR.h" 
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	IplImage *input_image = cvLoadImage("1.png",1);
	IplImage *depthmap = cvLoadImage("dep.png",0);
	// DIBR process
	IplImage *dibr = cvCreateImage(cvGetSize(input_image),8,3);
	DIBR(input_image, depthmap, dibr);
	cvShowImage("dibr",dibr); 
	cvSaveImage("DIBR_R.png",dibr);
	cvReleaseImage(&input_image);
	cvReleaseImage(&depthmap);
	cvReleaseImage(&dibr);
	cvWaitKey(0);
}