
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;




 //-----------------Draw Shapes and text-----------------//

int main() {
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 0));
	circle(img, Point(300, 300), 155, Scalar(0, 69, 255), 4); //thickness or FILLED
	rectangle(img, Point(200, 200), Point(400, 400), Scalar(255, 255, 0), 3); //thickness or FILLED
	line(img, Point(200, 200), Point(400, 400), Scalar(255, 255, 0), 3);
	line(img, Point(400, 200), Point(200, 400), Scalar(255, 255, 0), 3);
	putText(img, "huu loi", Point(200, 200),FONT_HERSHEY_COMPLEX,2, Scalar(5, 69, 255),2);
	imshow("img", img);

	
	waitKey(0);
	return 0;
}