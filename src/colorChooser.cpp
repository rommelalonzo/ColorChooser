#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(int argc, char** argv){
   int minR=0;
   int minG=0;
   int minB=0;
   int maxR=0;
   int maxG=0;
   int maxB=0;
   VideoCapture cap(0); // open the default camera
   cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
   cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
   if(!cap.isOpened())  // check if we succeeded
	return -1;

   //Constructs GUI windows
   cvNamedWindow("Frame");
   namedWindow("Choose RGB Values");
   createTrackbar("minR","Choose RGB Values",&minR,255);
   createTrackbar("minG","Choose RGB Values",&minG,255);
   createTrackbar("minB","Choose RGB Values",&minB,255);
   createTrackbar("maxR","Choose RGB Values",&maxR,255);
   createTrackbar("maxG","Choose RGB Values",&maxG,255);
   createTrackbar("maxB","Choose RGB Values",&maxB,255);

   for(;;){
	Mat frame;
	
   	CvScalar min_RGB = cvScalar(minR,minG,minB);
	CvScalar max_RGB = cvScalar(maxR,maxG,maxB);
        cap >> frame; // get a new frame from camera
	IplImage image;
	frame.();
	cvInRangeS(&image,min_RGB,max_RGB,&image);
        cvShowImage("Frame", &image);
        if(waitKey(30) >= 0) break;
   }
   // the camera will be deinitialized automatically in VideoCapture destructor
   return 0;
}
