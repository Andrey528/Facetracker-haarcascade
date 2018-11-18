#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	string mainWindow = "Main";
	string faceDetector = "FaceDetector";
	Mat frame;
	VideoCapture capture;
	CascadeClassifier face_cascade;
	face_cascade.load(".../opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");

	namedWindow(faceDetector, 0);

	capture.open(0);
	if (!capture.isOpened())
	{
		cout << "Не получилось открыть камеру";
		exit(1);
	}

	for (;;)
	{
		capture >> frame;
		
		// Detect faces
		std::vector<Rect> faces;
		face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		// Draw circles on the detected faces
		for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		imshow(faceDetector, frame);
		if (waitKey(33) == 27) break;
	}

	return 0;
}
