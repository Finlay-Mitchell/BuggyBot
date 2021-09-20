#include <iostream>
#include <memory>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "src/utils.h"
#include "src/BrightestPixels/brightestPixels.h"

int main(int argc, const char** argv)
{
    cv::CommandLineParser parser(argc, argv, "{help h||}" "{face_cascade|C:/OpenCV/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml|Path to face cascade.}"
        "{capture|http://192.168.0.21:81/stream|stream input location.}"
        "{frameTitle|test|Sets the name of the frame.}");
    parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n" "You can use Haar or LBP features.\n\n");
    parser.printMessage();
    std::unique_ptr<Utils> utils = std::make_unique<Utils>();
    utils->CameraName = parser.get<std::string>("capture");
    cv::VideoCapture videoCapture(utils->CameraName);

    if (!videoCapture.isOpened())
    {
        std::cerr << "Cannot open the captrue device.";
        return -1;
    }

    cv::namedWindow("image");
    cv::Mat frame;

    while (true)
    {
        if (cv::waitKey(30) == 27)
        {
            return 0;
        }

        bool videoCaptureReadSuccess = videoCapture.read(frame);

        if (!videoCaptureReadSuccess)
        {
            std::cerr << "Cannot read a frame from the input stream";
            break;
        }

        cv::imshow("image", frame);


        brightestPixelDetection::detectBrighestPixels(frame);
    }
}