#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//-----------------Shapes Detection-----------------//

Mat img_gray, img_Blur, img_Canny, img_Dil, img_Erode;

void getContours(Mat imgDil, Mat img) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	string objType;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 10);
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;
		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objType = "Tri"; }
			if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) {
					objType = "Square";
				}
				else {
					objType = "Rect";
				}

			}
			if (objCor > 4) { objType = "Circle"; }
			
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), 7);
			//putText(img, objType, {boundRect[i].x+35,boundRect[i].y-5}, FONT_HERSHEY_COMPLEX, 0.75, Scalar(5, 69, 255), 1);
			putText(img, objType, boundRect[i].tl() + Point(35, -5), FONT_HERSHEY_PLAIN, 1, Scalar(5, 69, 255), 2);

		}

	}
}

void Preprocessing(Mat img) {
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_Blur, Size(3, 3), 2, 2);
	Canny(img_Blur, img_Canny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_Canny, img_Dil, kernel);
	getContours(img_Dil, img);
	imshow("img_Blur", img_Blur);
	imshow("img_Dil", img_Dil);
}
void main() {

	VideoCapture cap(0);
	Mat img;
	while (true) {
		cap.read(img);
		Preprocessing(img);
		imshow("img", img);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}
	cap.release();
	destroyAllWindows();

	//imshow("img_gray", img_gray);
	//imshow("img_Blur", img_Blur);
	//imshow("img_Canny", img_Canny);
	//imshow("img_Dil", img_Dil);
	waitKey(0);
}