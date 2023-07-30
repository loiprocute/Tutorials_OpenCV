
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;






//////////////////     Face Detection     ////////////////////


				//img

//void main() {
//	string path ="Resources/avt.jpg";
//	Mat img = imread(path);
//
//	CascadeClassifier faceCascade;
//	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
//	if (faceCascade.empty()) {
//		cout << "XML file not found" << endl;
//	}
//	vector<Rect> faces;
//	faceCascade.detectMultiScale(img, faces, 1.1, 10);
//	for (int i = 0; i < faces.size(); i++) {
//		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
//	}
//	imshow("output img", img);
//
//	waitKey(0);
//}

						 //Video

void main() {
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) {
		cout << "XML file not found" << endl;
	}

	VideoCapture cap(0);
	Mat img;
	vector<Rect> faces;
	while (true) {
		cap.read(img);
		faceCascade.detectMultiScale(img, faces, 1.1, 10);
		for (int i = 0; i < faces.size(); i++) {
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
			putText(img, "Loi", faces[i].tl() + Point(10, -5), FONT_HERSHEY_PLAIN, 1, Scalar(5, 69, 255), 2);
		}
		imshow("img", img);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}
	cap.release();
	destroyAllWindows();
	waitKey(0);
}