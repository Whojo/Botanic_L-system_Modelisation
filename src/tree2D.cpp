#include <cstddef>
#include <iostream>
#include <cmath>
#include <functional>
#include <ctime>
#include <random>

#include "drawer2D.hpp"

#include "core/l_system.hpp"

using namespace cv; 

using Palette = std::function<Scalar(char)>;
using LengthController = std::function<double(char)>;


void turtle(Drawer &drawer, std::string sentence, double angle,
            LengthController length_controller,
            Palette palette = [](const char) -> Scalar { return {0, 0, 0};},
            const int thickness = 2)
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

int main()
{
    std::srand(std::time(0));

    int height = 1200;
    int width = 1200;

    int base = height - 20;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    LengthController length{[](char) {return 4;}};
    Drawer drawer = Drawer(height, width, starting);


  //   std::string axiom_a = "F";
  //   std::vector<core::Rule> productions_a = {
  //   core::Rule{ 'F', "F[+F]F[-F]F"},
  // };

  //   core::LSystem lsys_a{ axiom_a, productions_a };

  //   auto generated_a = lsys_a.generate(5);

    double pi7 = pi / 7; // 25,7°
  //   turtle(drawer, generated_a, pi7, length);
  //   drawer.write_img("example/a_example.png");

  //   /* ----------------- */
  //   drawer = Drawer(height, width, starting);
  //   std::string axiom_b = "F";
  //   std::vector<core::Rule> productions_b = {
  //   core::Rule{ 'F', "F[+F]F[-F][F]"},
  // };

  //   core::LSystem lsys_b{ axiom_b, productions_b };

  //   auto generated_b = lsys_b.generate(5);

    double pi9 = pi / 9; // 20°
  //   turtle(drawer, generated_b, pi7, length);
  //   drawer.write_img("example/b_example.png");

  //   /* ----------------- */
  //   drawer = Drawer(height, width, starting);
  //   std::string axiom_c = "F";
  //   std::vector<core::Rule> productions_c = {
  //   core::Rule{ 'F', "FF-[-F+F+F]+[+F-F-F]"},
  // };

  //   core::LSystem lsys_c{ axiom_c, productions_c };

  //   auto generated_c = lsys_c.generate(4);

    double pi8 = pi / 8; // 22.5°
  //   turtle(drawer, generated_c, pi7, length);
  //   drawer.write_img("example/c_example.png");

  //   /* ----------------- */

    // drawer = Drawer(height, width, starting);
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
    turtle(drawer, generated_d, pi9, length, palette_d);
    drawer.write_img("example/d_example.png");

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
    turtle(drawer, generated_e, pi7, length, palette_d);
    drawer.write_img("example/e_example.png");

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

    turtle(drawer, generated_f, pi8, length, palette_d);
    drawer.write_img("example/f_example.png");

    // /* ----------------- */

    length = [](char c) {
      if (c == 'G' or c == 'H')
        return 3;
      return 15;
    };
    drawer = Drawer(500, 1000, {620, 430});
    std::string axiom_leaf = "HG";
    std::vector<core::Rule> productions_leaves = {
      core::Rule{'G',  "G+[+G-G-G]-[-G+G+G]"},
      core::Rule{'H',  "H-[-H+H+H]+[+H-H-H]"},
    };

    core::LSystem lsys_leaves{ axiom_leaf, productions_leaves };
    auto leaves = lsys_leaves.generate(4);

    turtle(drawer, leaves, pi / 12, length, [](const char) -> Scalar {return {2, 4, 33};}, 1);
    drawer.write_img("example/g_leaves_right_example.png");

    // /* ----------------- */

    // drawer = Drawer(500, 1000, {620, 430});
    drawer = Drawer("example/Background3.jpg", {620, 340});
    std::string axiom_g = "F[+G][--H]";
    // ** Alphabet **
    // F: Trunc base
    // L: Left branch
    // R: Right branch
    // G: Left leaves
    // H: Right leaves
    std::vector<core::Rule> productions_g_trunc = {
      core::Rule{'F',  "F[+L][--R]"},
      core::Rule{'G', std::vector<std::string>{"L[+G][-H]", "L[+G]"} },
      core::Rule{'H', std::vector<std::string>{"R[+G][-H]", "R[-H]"} },
    };

    core::LSystem lsys_trunc{ axiom_g, productions_g_trunc };
    auto trunc = lsys_trunc.generate(4);

    core::LSystem lsys_tree{ trunc, productions_leaves };
    auto tree = lsys_tree.generate(3);

    turtle(drawer, tree, pi / 12, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("example/g_example.png");

    // /* ----------------- */

    std::string axiom_cont = "bcaaaaaaa";
    std::vector<core::Rule> productions_cont = {
      core::Rule{'b', "a"},
      core::Rule{'a', "b", [](std::optional<char> left, std::optional<char>) {return left == 'b';} },
    };

    core::LSystem lsys_cont{ axiom_cont, {}, productions_cont, "c" };
    std::cout << axiom_cont            << std::endl;
    std::cout << lsys_cont.generate(1) << std::endl;
    std::cout << lsys_cont.generate(2) << std::endl;
    std::cout << lsys_cont.generate(3) << std::endl;
    std::cout << lsys_cont.generate(4) << std::endl;

    return 0;
}
