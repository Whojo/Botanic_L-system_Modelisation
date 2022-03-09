#include "drawer2D.hpp"

#include "opencv2/highgui.hpp"

Drawer::Drawer(int height, int width, cv::Point start, int length)
{
    window = cv::Mat(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
    state = State{ pi/2, length, start };
}
void Drawer::draw_line(cv::Scalar color, int thickness)
{
    cv::Point dest(state.position.x + state.length * cos(state.angle),
                   state.position.y - state.length * sin(state.angle));
    cv::line(window, state.position, dest, color, thickness);
    state.position = dest;
}
void Drawer::draw_line()
{
    draw_line(cv::Scalar(0, 0, 0), 2);
}
void Drawer::space()
{
    state.position =
        cv::Point(state.position.x + state.length * cos(state.angle),
                  state.position.y - state.length * sin(state.angle));
}

// void Drawer::set_state(double angle, int length, cv::Point position)
// {
//     state.angle = angle;
//     state.length = length;
//     state.position = position;
// }
void Drawer::add_angle(double angle)
{
    state.angle += angle;
}
void Drawer::set_length(int length)
{
    state.length = length;
}

void Drawer::push_state()
{
    stack.push_front(State{state.angle, state.length, state.position});
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
