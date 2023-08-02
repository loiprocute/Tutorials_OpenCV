#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;






////////////////// Virtual Paint    ////////////////////

Mat frame;

vector<vector<int>> newPoints ;
vector<vector<int>> myColors {{46, 90, 120, 147, 255, 255} };
vector<Scalar> myColorValues{{255, 0, 255}};


Point getContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	string objType;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 10);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;
		
		if (area > 50) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y ;

			drawContours(frame, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(frame, boundRect[i].tl(), boundRect[i].br(), 7);
			//putText(img, objType, {boundRect[i].x+35,boundRect[i].y-5}, FONT_HERSHEY_COMPLEX, 0.75, Scalar(5, 69, 255), 1);
			putText(frame, objType, boundRect[i].tl() + Point(35, -5), FONT_HERSHEY_PLAIN, 1, Scalar(5, 69, 255), 2);

		}

	}
	return myPoint;
}

vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV); 
	for (int i = 0; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		Point myPoint = getContours(mask);
		circle(frame, myPoint, 10, Scalar(255, 0, 255), FILLED);
		if (myPoint.x != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
		
	}
	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {
	for (int i = 0; i < newPoints.size(); i++) {
		circle(frame, Point(newPoints[i][0],newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

void main() {
	VideoCapture cap(0);
	while (true) {
		cap.read(frame);
		newPoints = findColor(frame);
		drawOnCanvas(newPoints, myColorValues);
		imshow("Contours", frame);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}
	cap.release();
	destroyAllWindows();

}