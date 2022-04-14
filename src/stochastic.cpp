#include <ctime>
#include <random>

#include "core/l_system.hpp"
#include "utils/turtle.hpp"

using namespace std::string_literals;

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

    std::vector<core::Rule> productions_leaves = {
      core::Rule{'G',  "G+[+G-G-G]-[-G+G+G]"s},
      core::Rule{'H',  "H-[-H+H+H]+[+H-H-H]"s},
    };

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
      core::Rule{'F',  "F[+L][--R]"s},
      core::Rule{'G', std::vector<core::State>{"L[+G][-H]"s, "L[+G]"s} },
      core::Rule{'H', std::vector<core::State>{"R[+G][-H]"s, "R[-H]"s} },
    };

    core::LSystem lsys_trunc{ axiom_g, productions_g_trunc };
    auto trunc = lsys_trunc.generate(4);

    core::LSystem lsys_tree{ trunc, productions_leaves };
    auto tree = lsys_tree.generate(3);

    turtle2D(drawer, tree.get_letters(), pi / 12, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("output/stochastic/example.png");
}
