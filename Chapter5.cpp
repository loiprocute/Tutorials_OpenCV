
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-----------------Warp Perspective-----------------//


float w = 250, h = 350;



int main() {
	string path = "Resources/card.jpg";
	Mat img = imread(path);
	Point2f src[4] = { {445,46},{588,39},{459,231},{615,229} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 5, Scalar(0, 69, 255), FILLED);
	}

	Mat matrix, imgWarp;
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	
	imshow("imgWarp", imgWarp);
	imshow("img", img);

	waitKey(0);
	return 0;
}