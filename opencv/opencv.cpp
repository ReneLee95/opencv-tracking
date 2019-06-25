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
			//ī�޶�κ��� �̹��� ������
			cap >> frame_original;
		}
		catch (Exception& e) {
			cerr << "Execption occurred." << endl;
			frame_valid = false;
		}

		if (frame_valid) {
			try {
				Mat grayframe;
				//gray scale�� ��ȯ
				cvtColor(frame_original, grayframe, COLOR_BGR2GRAY);
				//histogram ���
				equalizeHist(grayframe, grayframe);

				//�̹��� ǥ�ÿ� ����
				vector<Rect> faces;

				//���� ��ġ�� ������ Ž���Ѵ�.

	//detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1,
	//int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())
	//image ���� �̹���
	//objects �� ���� ��ġ�� ���� ����
	//scaleFactor �̹��� ������
	//minNeighbors �� ���� �ĺ����� ����
	//flags ���� cascade�� �����ϴ� cvHaarDetectObjects �Լ� ����
	//���ο� cascade������ ������� �ʴ´�.
	//minSize ������ �ּ� ��ü ������
	//maxSize ������ �ִ� ��ü ������
				face_classifier.detectMultiScale(grayframe, faces, 1.3, 3, 0,//CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
					Size(100, 100));

				for (int i = 0; i < faces.size(); i++) {
					Point lb(faces[i].x + faces[i].width,
						faces[i].y + faces[i].height);
					Point tr(faces[i].x, faces[i].y);
					//rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
					//img ������ �̹���
					//pt1 �׸� ������ ������
					//pt2 pt1�� �ݴ��� ������
					//color ������ ����
					//thickness ������ ���ε��� �β� ���� �Ǵ� CV_FILLED�� �ָ� ���ڸ� ä���.
					//lineType ������ ��� line()�Լ� Ȯ���ϱ�
					//shift ?? Number of fractional bits in the point coordinates.
					//����Ʈ ��ǥ�� �м� ��Ʈ�� ��??
					rectangle(frame_original, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
				}
				//�����쿡 �̹��� �׸���
				imshow("Face", frame_original);
			}
			catch (Exception& e) {
				cerr << "Exception occurred. face" << endl;

			}
			//Ű �Է� ���
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



