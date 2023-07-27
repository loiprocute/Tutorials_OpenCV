
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;






//////////////////     Basic Functions                    ////////////////////

void main() {
	string path = "Resources/avt.jpg";
	Mat img = imread(path);
	Mat img_gray, img_Blur, img_Canny, img_Dil, img_Erode ;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img, img_Blur, Size(7,7), 5, 0);
	Canny(img_Blur, img_Canny,50,150);


	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_Canny, img_Dil,kernel);
	erode(img_Dil, img_Erode, kernel);

	imshow("img", img);
	imshow("img_gray", img_gray);
	imshow("img_Blur", img_Blur);
	imshow("img_Canny", img_Canny);
	imshow("img_Dil", img_Dil);
	imshow("img_Erode", img_Erode);

	waitKey(0);
}	
