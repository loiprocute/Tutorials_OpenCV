#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main()
{
	string path = "Resources/vid.mp4";
	VideoCapture cap(0);
	Mat img;
	while (true) {
		cap.read(img);
		imshow("img", img);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}
	cap.release();
	destroyAllWindows();
	
}
 