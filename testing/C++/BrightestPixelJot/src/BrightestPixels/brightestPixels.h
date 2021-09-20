#pragma once

#ifndef BRIGHTESTPIXELS_H
#define BRIGHTESTPIXELS_H

#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "../utils.h"

class brightestPixelDetection : Utils
{
public:
	static void detectBrighestPixels(cv::Mat);
};

#endif