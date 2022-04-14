#include "utils/drawer2D.hpp"

#include "opencv2/highgui.hpp"


Drawer::Drawer(const std::string background_img, cv::Point2d start)
{
    auto img = imread(background_img, cv::IMREAD_COLOR);
    window = cv::Mat(img);
    state = State{ pi/2, start };
}

Drawer::Drawer(int height, int width, cv::Point2d start)
{
    window = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
    state = State{ pi/2, start };
}
Drawer::Drawer(int height, int width, cv::Point2d start, double start_angle)
{
    window = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
    state = State{ start_angle, start };
}

void Drawer::draw_line(cv::Scalar color, int thickness, double length)
{
    cv::Point2d dest(state.position.x + length * cos(state.angle),
                     state.position.y - length * sin(state.angle));
    cv::line(window, state.position, dest, color, thickness);
    state.position = dest;
}

void Drawer::draw_line(int thickness, double length)
{
    draw_line(cv::Scalar(0, 0, 0), thickness, length);
}

void Drawer::space(double length)
{
    state.position =
        cv::Point2d(state.position.x + length * cos(state.angle),
                    state.position.y - length * sin(state.angle));
}

void Drawer::add_angle(double angle)
{
    state.angle += angle;
}

void Drawer::push_state()
{
    stack.push_front(State{state.angle, state.position});
}

bool Drawer::pop_state()
{
    if (!stack.empty())
    {
        // pop_front return void :c
        state = stack.front();
        stack.pop_front();
        return true;
    }
    return false;
}

void Drawer::show_window(std::string window_name)
{
    cv::namedWindow(window_name, cv::WINDOW_GUI_NORMAL | cv::WINDOW_AUTOSIZE);
    cv::imshow(window_name, window);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void Drawer::show_window()
{
    show_window("");
}

void Drawer::write_img(std::string filename)
{
    imwrite(filename, window);
}
