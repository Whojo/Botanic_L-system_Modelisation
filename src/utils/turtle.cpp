#include "turtle.hpp"


void turtle2D(Drawer &drawer, std::string sentence, double angle,
            LengthController length_controller, Palette palette,
            const int thickness)
{
    for (size_t i = 0; i < sentence.length(); i++)
    {
        char c = sentence[i];
        switch(c)
        {
            case 'X':
                break;
            case '+':
                drawer.add_angle(angle);
                break;
            case '-':
                drawer.add_angle(-angle);
                break;
            case '[':
                drawer.push_state();
                break;
            case ']':
                if (!drawer.pop_state())
                    std::cerr << "Empty pop" << std::endl;
                break;
            default:
                drawer.draw_line(palette(c), thickness, length_controller(c));
        }
    }
}
