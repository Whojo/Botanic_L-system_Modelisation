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

    std::string axiom_a = "F";
    std::vector<core::Rule> productions_a = {
    core::Rule{ 'F', "F[+F]F[-F]F"},
  };

    core::LSystem lsys_a{ axiom_a, productions_a };

    auto generated_a = lsys_a.generate(5);

    turtle2D(drawer, generated_a, pi7, length);
    drawer.write_img("output/brackets/a_example.png");

  //   /* ----------------- */
    drawer = Drawer(height, width, starting);
    std::string axiom_b = "F";
    std::vector<core::Rule> productions_b = {
    core::Rule{ 'F', "F[+F]F[-F][F]"},
  };

    core::LSystem lsys_b{ axiom_b, productions_b };

    auto generated_b = lsys_b.generate(5);

    turtle2D(drawer, generated_b, pi7, length);
    drawer.write_img("output/brackets/b_example.png");

  //   /* ----------------- */
    drawer = Drawer(height, width, starting);
    std::string axiom_c = "F";
    std::vector<core::Rule> productions_c = {
    core::Rule{ 'F', "FF-[-F+F+F]+[+F-F-F]"},
  };

    core::LSystem lsys_c{ axiom_c, productions_c };

    auto generated_c = lsys_c.generate(4);

    turtle2D(drawer, generated_c, pi7, length);
    drawer.write_img("output/brackets/c_example.png");

  //   /* ----------------- */

    drawer = Drawer(height, width, starting);
    std::string axiom_d = "X";
    std::vector<core::Rule> productions_d = {
      core::Rule{ 'X', "H[+X]H[-X]+X"},
      core::Rule{ 'F', "FF"},
      core::Rule{ 'H', "FF"},
    };

    core::LSystem lsys_d{ axiom_d, productions_d };

    auto generated_d = lsys_d.generate(7);

    Palette palette_d = [](const char c) -> Scalar {
      if (c == 'H')
        return {28,116,72}; // Green
      return {12,47,55}; // Brown
    };
    turtle2D(drawer, generated_d, pi9, length, palette_d);
    drawer.write_img("output/brackets/d_example.png");

  //   /* ----------------- */

    drawer = Drawer(height, width, starting);
    std::string axiom_e = "X";
    std::vector<core::Rule> productions_e = {
      core::Rule{ 'X', "H[+X][-X]HX"},
      core::Rule{ 'H', "FF"},
      core::Rule{ 'F', "FF"},
    };

    core::LSystem lsys_e{ axiom_e, productions_e };

    auto generated_e = lsys_e.generate(7);
    turtle2D(drawer, generated_e, pi7, length, palette_d);
    drawer.write_img("output/brackets/e_example.png");

    // /* ----------------- */

    drawer = Drawer(height, width, starting);
    std::string axiom_f = "X";
    std::vector<core::Rule> productions_f = {
      core::Rule{ 'X', "H-[[X]+X]+H[+HX]-X"},
      core::Rule{ 'H', "FF"},
      core::Rule{ 'F', "FF"},
    };

    core::LSystem lsys_f{ axiom_f, productions_f };

    auto generated_f = lsys_f.generate(5);

    turtle2D(drawer, generated_f, pi8, length, palette_d);
    drawer.write_img("output/brackets/f_example.png");

    return 0;
}
