#include <ctime>
#include <random>

#include "core/l_system.hpp"
#include "utils/turtle.hpp"

int main()
{
    std::srand(std::time(0));

    int height = 1200;
    int width = 1200;

    int base = height - 20;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    LengthController length{[](char) {return 4;}};
    Drawer drawer = Drawer(height, width, starting);

    double pi7 = pi / 7; // 25,7°
    double pi8 = pi / 8; // 22.5°
    double pi9 = pi / 9; // 20°

    // /* ----------------- */
    length = [](char) {
      return 5;
    };
    drawer = Drawer(height, width, starting);
    std::string axiom_fractale_test = "F-F-F-F";
    std::vector<core::Rule> productions_fractale_test = {
        {'F', "FF-F-F-F-FF", [](cstr &left, cstr &right){return true;}}
  };
    core::LSystem lsys_fractale_test{ axiom_fractale_test, {}, productions_fractale_test, "" };
    auto tree_fractale = lsys_fractale_test.generate(4);
    turtle2D(drawer, tree_fractale, pi / 2, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("output/fractals/example.png");
}
