#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/highgui.hpp"
#include <cmath>
using namespace cv;
using namespace std;
int main()
{
    const double pi = acos(-1);
    int height = 800;
    int width = 800;
    Mat whiteMatrix(height, width, CV_8UC3,
                    Scalar(255, 255, 255)); // Declaring a white matrix//
    int base = height - 50;
    int length = 100;
    double alpha = pi / 4;
    Point2d starting(width / 2.f, base); // Starting Point of the line
    Point2d ending(width / 2.f, base - length); // Ending Point of the line
    int thickness = 2; // thickens of the line
    auto white = Scalar(0,0,0);
    line(whiteMatrix, starting, ending, white,
         thickness); // using line() function to draw the line//
    Point2d result(ending.x - length * cos(alpha), ending.y - length * sin(alpha));
    line(whiteMatrix, ending, result, white, thickness);
    namedWindow("GrayImage", WINDOW_GUI_NORMAL | WINDOW_AUTOSIZE);
    imshow("GrayImage", whiteMatrix); // showing the line//
    imwrite("image_nulle.png", whiteMatrix);
    waitKey(0); // Waiting for KeyStroke
    destroyAllWindows(); 
    return 0;
}
