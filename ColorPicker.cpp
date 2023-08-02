
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-----------------Color Detection-----------------//
Mat imgHSV, mask;
int hmin = 46, smin = 90, vmin = 120;
int hmax = 147, smax = 255, vmax = 255;

VideoCapture cap(0);
Mat img;

void main() {
	
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue min", "Trackbars", &hmin, 179);
	createTrackbar("Hue max", "Trackbars", &hmax, 179);
	createTrackbar("Sat min", "Trackbars", &smin, 255);
	createTrackbar("Sat max", "Trackbars", &smax, 255);
	createTrackbar("Val min", "Trackbars", &vmin, 255);
	createTrackbar("Val max", "Trackbars", &vmax, 255);

	while (1) {
		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("img ", img);
		imshow("imgMask ", mask);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

}