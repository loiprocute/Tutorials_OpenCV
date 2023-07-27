
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-----------------Color Detection-----------------//
Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 146;
int hmax = 179, smax = 255, vmax = 255;
void main() {
	string path = "Resources/card.jpg";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue min", "Trackbars", &hmin, 179);
	createTrackbar("Hue max", "Trackbars", &hmax, 179);
	createTrackbar("Sat min", "Trackbars", &smin, 255);
	createTrackbar("Sat max", "Trackbars", &smax, 255);
	createTrackbar("Val min", "Trackbars", &vmin, 255);
	createTrackbar("Val max", "Trackbars", &vmax, 255);
	while (1) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("img ", img);
		imshow("imgHSV ", imgHSV);
		imshow("imgMask ", mask);
		waitKey(1);
	}
	
}