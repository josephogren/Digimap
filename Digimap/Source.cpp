#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{   
    std::cout << "DigiMap v1.0" << std::endl;

    Mat input_image = imread("C:\\Dev\\Repo\\cpp\\Digimap\\x64\\Debug\\input_image.jpg", IMREAD_GRAYSCALE);

    if (input_image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Detect corners using Harris corner detector
    Mat corner_image;
    cornerHarris(input_image, corner_image, 2, 3, 0.04);

    // Normalize corner response image for display
    Mat corner_norm;
    normalize(corner_image, corner_norm, 0, 255, NORM_MINMAX, CV_8UC1);

    // Display corner response image
    imshow("Corner Response Image", corner_norm);
    waitKey(0);

    return 0;
}