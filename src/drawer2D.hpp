#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/highgui.hpp"
#include <deque>
#include <optional>

//const double pi = acos(-1);
const double pi = M_PI;

struct State
{
public:
    double angle;
    int length;
    cv::Point position;
};

class Drawer
{
public:
    Drawer(int height, int width, cv::Point start, int length);

    // Draw a line based on the current state of the Drawer
    // The state is updated
    void draw_line(cv::Scalar color, int thickness);
    void draw_line();
    // Only update the state
    void space();

    //void set_state(double angle, int length, cv::Point position); Useless
    void add_angle(double angle);
    void set_length(int length);

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
