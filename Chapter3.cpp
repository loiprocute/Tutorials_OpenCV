
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//#include <opencv2/core/utils/logger.hpp>
//cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_VERBOSE);


int main() {
	string path = "Resources/avt.jpg";
	Mat img = imread(path);
	Mat imgResize, imgCrop;
	/*cout << "img size ============ " << img.size() << endl;*/
	//----------Resize----------//
	//resize(img, imgResize, Size(500, 560));
	resize(img, imgResize, Size(),0.5, 0.5);

	//----------Crop----------//
	Rect roi(300, 300, 300, 250);
	imgCrop = img(roi);



	/*cout << "imgResize size ============ " << imgResize.size() << endl;*/
	imshow("img", img);
	imshow("img Resize", imgResize);
	imshow("img Crop", imgCrop);
	waitKey(0);
	return 0;
}