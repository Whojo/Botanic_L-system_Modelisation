#include <iostream>
#include <cmath>
#include "drawer2D.hpp"

using namespace cv; 

int main()
{
    int height = 800;
    int width = 800;

    int length = 100;
    int base = height - 50;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    Drawer drawer = Drawer(height, width, starting, length);

    // Drawing F[+F][-F[-F]F]F[+F][-F] exemple page 24 abop.pdf

    drawer.draw_line();

    drawer.push_state();
    drawer.add_angle(pi / 4); 
    drawer.draw_line();
    if (!drawer.pop_state())
      std::cerr << "Failed" << std::endl;

    drawer.push_state();
    drawer.add_angle(-pi / 4);
    drawer.draw_line();
    drawer.push_state();
    drawer.add_angle(-pi / 4);
    drawer.draw_line();
    if (!drawer.pop_state())
      std::cerr << "Inner bracket Failed" << std::endl;
    drawer.draw_line();
    if (!drawer.pop_state())
      std::cerr << "Failed" << std::endl;

    drawer.draw_line();

    drawer.push_state();
    drawer.add_angle(pi / 4);
    drawer.draw_line();
    if (!drawer.pop_state())
      std::cerr << "Failed" << std::endl;

    drawer.push_state();
    drawer.add_angle(-pi / 4);
    drawer.draw_line();
    if (!drawer.pop_state())
      std::cerr << "Failed" << std::endl;
    

    drawer.write_img("drawio.png");

    return 0;
}
