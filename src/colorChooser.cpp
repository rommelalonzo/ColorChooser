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
   CvCapture* capture = cvCaptureFromCAM(0);
   cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
   cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);

   //Constructs GUI windows
   cvNamedWindow("Frame");
   cvNamedWindow("ColorThreshold");
   namedWindow("Choose RGB Values");
   createTrackbar("minR","Choose RGB Values",&minR,255);
   createTrackbar("minG","Choose RGB Values",&minG,255);
   createTrackbar("minB","Choose RGB Values",&minB,255);
   createTrackbar("maxR","Choose RGB Values",&maxR,255);
   createTrackbar("maxG","Choose RGB Values",&maxG,255);
   createTrackbar("maxB","Choose RGB Values",&maxB,255);

   for(;;){
   	CvScalar min_RGB = cvScalar(minR,minG,minB);
	CvScalar max_RGB = cvScalar(maxR,maxG,maxB);
        // get the raw image
    	IplImage* frame = cvQueryFrame(capture);
	IplImage* segmentated = cvCreateImage(cvGetSize(frame),8,1);
	cvInRangeS(frame,min_RGB,max_RGB,segmentated);
        cvShowImage("Frame", frame);
	cvShowImage("ColorThreshold",segmentated);
        if(waitKey(30) >= 0) break;
   }
   // the camera will be deinitialized automatically in VideoCapture destructor
   return 0;
}
