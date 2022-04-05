#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/highgui.hpp"
#include <deque>
#include <optional>
#include <string>

//const double pi = acos(-1);
const double pi = M_PI;

struct State
{
public:
    double angle;
    cv::Point2d position;
};

class Drawer
{
public:
    Drawer(const std::string background_img, cv::Point2d start);
    Drawer(int height, int width, cv::Point2d start);

    // Draw a line based on the current state of the Drawer
    // The state is updated
    void draw_line(cv::Scalar color, int thickness, double length);
    void draw_line(int thickness = 2, double length = 1);
    // Only update the state
    void space(double length);

    void add_angle(double angle);

    void push_state();
    bool pop_state();
    
    void show_window(std::string window_name);
    void show_window();
    void write_img(std::string filename);

private:
    cv::Mat window;
    State state;
    std::deque<State> stack;
};
