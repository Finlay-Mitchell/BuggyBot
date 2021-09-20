#include "brightestPixels.h"

void brightestPixelDetection::detectBrighestPixels(cv::Mat frame)
{
	double minVal, maxVal = 0;
	int maxLoc;
	cv::Mat grayImage;
	cv::Mat hsv[3];

	cv::cvtColor(frame, grayImage, cv::COLOR_RGB2GRAY);
	cv::split(grayImage, hsv);
	cv::imshow("r", hsv[0]);
	//cv::imshow("g", hsv[1]);
	//cv::imshow("b", hsv[2]);


	while (true)
	{
		
	}
}