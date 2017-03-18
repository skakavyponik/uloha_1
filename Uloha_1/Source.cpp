#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
	Mat src, src_gray;
	Mat srcp, src_grayp;

	/// Read the image
	src = imread("D:/data/frame2_30.jpg");
	srcp = imread("D:/data/frame1_30.jpg");

	if (!src.data || !srcp.data)
	{
		return -1;
	}

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);
	cvtColor(srcp, src_grayp, CV_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);
	GaussianBlur(src_grayp, src_grayp, Size(9, 9), 2, 2);

	vector<Vec3f> circles;
	vector<Vec3f> circlesp;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 16, 120, 50, 0, 0);
	HoughCircles(src_grayp, circlesp, CV_HOUGH_GRADIENT, 1, src_gray.rows / 16, 120, 50, 0, 0);

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	for (size_t i = 0; i < circlesp.size(); i++)
	{
		Point center(cvRound(circlesp[i][0]), cvRound(circlesp[i][1]));
		int radius = cvRound(circlesp[i][2]);
		// circle center
		circle(srcp, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(srcp, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
	namedWindow("lave", CV_WINDOW_AUTOSIZE);
	imshow("lave", src);
	namedWindow("prave", CV_WINDOW_AUTOSIZE);
	imshow("prave", srcp);

	waitKey(0);
	return 0;
}