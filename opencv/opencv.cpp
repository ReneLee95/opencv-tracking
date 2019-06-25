#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tracking.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core_c.h>
#include <deque>
#include <vector>
#include "objdetect_c.h"
#include <opencv2/opencv.hpp>
#include "save.h"
#include <stdlib.h>
using namespace cv;
using namespace std;

int main(int, char**)
{
	int deviceID = 1;            
	CascadeClassifier face_classifier;
	face_classifier.load("haarcascade_frontalface_default.xml");
	VideoCapture cap(deviceID);

	namedWindow("Face", 1);


	Mat frame;
	//--- INITIALIZE VIDEOCAPTURE
	// open the default camera using default API
	 cap.open(1);
	// OR advance usage: select any API backend
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	// open selected camera using selected API
	cap.open(deviceID + apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;
	while(1)
	{
		bool frame_valid = true;

		Mat frame_original;
		Mat frame;

		try {
			//카메라로부터 이미지 얻어오기
			cap >> frame_original;
		}
		catch (Exception& e) {
			cerr << "Execption occurred." << endl;
			frame_valid = false;
		}

		if (frame_valid) {
			try {
				Mat grayframe;
				//gray scale로 변환
				cvtColor(frame_original, grayframe, COLOR_BGR2GRAY);
				//histogram 얻기
				equalizeHist(grayframe, grayframe);

				//이미지 표시용 변수
				vector<Rect> faces;

				//얼굴의 위치와 영역을 탐색한다.

	//detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1,
	//int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())
	//image 실제 이미지
	//objects 얼굴 검출 위치와 영역 변수
	//scaleFactor 이미지 스케일
	//minNeighbors 얼굴 검출 후보들의 갯수
	//flags 이전 cascade와 동일하다 cvHaarDetectObjects 함수 에서
	//새로운 cascade에서는 사용하지 않는다.
	//minSize 가능한 최소 객체 사이즈
	//maxSize 가능한 최대 객체 사이즈
				face_classifier.detectMultiScale(grayframe, faces, 1.3, 3, 0,//CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
					Size(100, 100));

				for (int i = 0; i < faces.size(); i++) {
					Point lb(faces[i].x + faces[i].width,
						faces[i].y + faces[i].height);
					Point tr(faces[i].x, faces[i].y);
					//rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
					//img 적용할 이미지
					//pt1 그릴 상자의 꼭지점
					//pt2 pt1의 반대편 꼭지점
					//color 상자의 색상
					//thickness 상자의 라인들의 두께 음수 또는 CV_FILLED를 주면 상자를 채운다.
					//lineType 라인의 모양 line()함수 확인하기
					//shift ?? Number of fractional bits in the point coordinates.
					//포인트 좌표의 분수 비트의 수??
					rectangle(frame_original, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
				}
				//윈도우에 이미지 그리기
				imshow("Face", frame_original);
			}
			catch (Exception& e) {
				cerr << "Exception occurred. face" << endl;

			}
			//키 입력 대기
			if (waitKey(10) >= 0) break;
		}


		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		if (waitKey(5) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}



