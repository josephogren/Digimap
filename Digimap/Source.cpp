/****************************************************************************/
/*                                                                          */
/*                            DIGIMAP v1.0                                  */
/*                      Digital Image Processing                            */
/*                                                                          */
/*  author: Joseph A.R. Ogren                                                */
/*  e-mail: joseph.ar.ogren@pm.me                                           */
/****************************************************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const int w = 400;
Mat src_gray;
int thresh = 100;
RNG rng(12345);

void basicDrawing();
int cornerHarrisDemo();
int shiTomasiDemo();
int boundingBox();
void thresh_callback(int, void*);
int brightnessAdjustment(double);


int main(int argc, char** argv)
{   
    std::cout << "DigiMap v1.0" << std::endl;
    
    
    //----- SELECT DEMO -----//

    //1. Basic Drawing
    //basicDrawing();
 
    //2. Feature Detection
    //cornerHarrisDemo();

    //3. Feature Detection 2
    //shiTomasiDemo();

    //4. Bounding Box
    boundingBox();

    //5. Brightness Adjustment
    //brightnessAdjustment(50);    


        
    waitKey(0);

    return 0;
}


void basicDrawing() 
{

    void MyEllipse(Mat img, double angle);
    void MyFilledCircle(Mat img, Point center);
    void MyPolygon(Mat img);
    void MyLine(Mat img, Point start, Point end);


    char atom_window[] = "Drawing 1: Atom";
    char rook_window[] = "Drawing 2: Rook";
    Mat atom_image = Mat::zeros(w, w, CV_8UC3);
    Mat rook_image = Mat::zeros(w, w, CV_8UC3);
    MyEllipse(atom_image, 90);
    MyEllipse(atom_image, 0);
    MyEllipse(atom_image, 45);
    MyEllipse(atom_image, -45);
    MyFilledCircle(atom_image, Point(w / 2, w / 2));
    MyPolygon(rook_image);
    rectangle(rook_image,
        Point(0, 7 * w / 8),
        Point(w, w),
        Scalar(0, 255, 255),
        FILLED,
        LINE_8);
    MyLine(rook_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
    MyLine(rook_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
    MyLine(rook_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
    MyLine(rook_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
    imshow(atom_window, atom_image);
    moveWindow(atom_window, 0, 200);
    imshow(rook_window, rook_image);
    moveWindow(rook_window, w, 200);

}

void MyEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    ellipse(img,
        Point(w / 2, w / 2),
        Size(w / 4, w / 16),
        angle,
        0,
        360,
        Scalar(255, 0, 0),
        thickness,
        lineType);

}

void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        w / 32,
        Scalar(0, 0, 255),
        FILLED,
        LINE_8);
}

void MyPolygon(Mat img)
{
    int lineType = LINE_8;
    Point rook_points[1][20];
    rook_points[0][0] = Point(w / 4, 7 * w / 8);
    rook_points[0][1] = Point(3 * w / 4, 7 * w / 8);
    rook_points[0][2] = Point(3 * w / 4, 13 * w / 16);
    rook_points[0][3] = Point(11 * w / 16, 13 * w / 16);
    rook_points[0][4] = Point(19 * w / 32, 3 * w / 8);
    rook_points[0][5] = Point(3 * w / 4, 3 * w / 8);
    rook_points[0][6] = Point(3 * w / 4, w / 8);
    rook_points[0][7] = Point(26 * w / 40, w / 8);
    rook_points[0][8] = Point(26 * w / 40, w / 4);
    rook_points[0][9] = Point(22 * w / 40, w / 4);
    rook_points[0][10] = Point(22 * w / 40, w / 8);
    rook_points[0][11] = Point(18 * w / 40, w / 8);
    rook_points[0][12] = Point(18 * w / 40, w / 4);
    rook_points[0][13] = Point(14 * w / 40, w / 4);
    rook_points[0][14] = Point(14 * w / 40, w / 8);
    rook_points[0][15] = Point(w / 4, w / 8);
    rook_points[0][16] = Point(w / 4, 3 * w / 8);
    rook_points[0][17] = Point(13 * w / 32, 3 * w / 8);
    rook_points[0][18] = Point(5 * w / 16, 13 * w / 16);
    rook_points[0][19] = Point(w / 4, 13 * w / 16);
    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 20 };
    fillPoly(img,
        ppt,
        npt,
        1,
        Scalar(255, 255, 255),
        lineType);
}

void MyLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = LINE_8;
    line(img,
        start,
        end,
        Scalar(0, 0, 0),
        thickness,
        lineType);
}

int cornerHarrisDemo() 
{

    Mat input_image = imread("C:\\Dev\\Repo\\cpp\\Digimap\\x64\\Debug\\input_image.jpg", IMREAD_GRAYSCALE);

    if (input_image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
        
    Mat corner_image;
    cornerHarris(input_image, corner_image, 2, 3, 0.04);

    // Normalize corner response image for display
    Mat corner_norm;
    normalize(corner_image, corner_norm, 0, 255, NORM_MINMAX, CV_8UC1);
    
    imshow("Corner Response Image", corner_norm);

    return 0;
}

int shiTomasiDemo() 
{
    
    Mat input_image = imread("C:\\Dev\\Repo\\cpp\\Digimap\\x64\\Debug\\input_image.jpg");

    if (input_image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    Mat gray;
    cvtColor(input_image, gray, COLOR_BGR2GRAY);

    // parameters for the Shi-Tomasi corner detector
    int max_corners = 100;
    double quality_level = 0.3;
    double min_distance = 7;
    int block_size = 7;
    
    vector<Point2f> corners;
    goodFeaturesToTrack(gray, corners, max_corners, quality_level, min_distance, Mat(), block_size, false, 0.04);
    
    for (int i = 0; i < corners.size(); i++)
    {
        circle(input_image, corners[i], 5, Scalar(0, 255, 0), -1);
    }
    
    namedWindow("Shi-Tomasi Corner Detector", WINDOW_NORMAL);
    imshow("Shi-Tomasi Corner Detector", input_image);

    return 0;
}

int boundingBox() 
{

    Mat input_image = imread("C:\\Dev\\Repo\\cpp\\Digimap\\x64\\Debug\\input_image.jpg");
    
   
    if (input_image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cvtColor(input_image, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    const char* source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, input_image);
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);
}

void thresh_callback(int, void*)
{
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);
    vector<vector<Point> > contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f>centers(contours.size());
    vector<float>radius(contours.size());
    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        boundRect[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
    }
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours_poly, (int)i, color);
        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
        circle(drawing, centers[i], (int)radius[i], color, 2);
    }
    imshow("Contours", drawing);
}

int brightnessAdjustment(double beta) 
{

    Mat input_image = imread("C:\\Dev\\Repo\\cpp\\Digimap\\x64\\Debug\\input_image.jpg");
    Mat output_image;

    if (input_image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    input_image.convertTo(output_image, -1, 1, beta);

    string adjImage = "Brightness Adjusted Image";
    namedWindow(adjImage, WINDOW_NORMAL);
    imshow(adjImage, output_image);

    return 0;
}
