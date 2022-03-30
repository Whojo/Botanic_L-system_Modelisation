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

    LengthController length{[](char c) {
      if (c == 'G' or c == 'H')
        return 3;
      return 15;
    }};
    Drawer drawer = Drawer(height, width, starting);

    double pi7 = pi / 7; // 25,7°
    double pi8 = pi / 8; // 22.5°
    double pi9 = pi / 9; // 20°

    drawer = Drawer(500, 1000, {620, 430});
    std::string axiom_leaf = "HG";
    std::vector<core::Rule> productions_leaves = {
      core::Rule{'G',  "G+[+G-G-G]-[-G+G+G]"},
      core::Rule{'H',  "H-[-H+H+H]+[+H-H-H]"},
    };

    core::LSystem lsys_leaves{ axiom_leaf, productions_leaves };
    auto leaves = lsys_leaves.generate(4);

    turtle2D(drawer, leaves, pi / 12, length, [](const char) -> Scalar {return {2, 4, 33};}, 1);
    drawer.write_img("output/stochastic/g_leaves_right_example.png");

    // /* ----------------- */

    drawer = Drawer("images/Background3.jpg", {620, 340});
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

    turtle2D(drawer, tree, pi / 12, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("output/stochastic/example.png");
}
