#include "core/l_system.hpp"
#include "utils/turtle.hpp"

int main()
{
    std::cout << "Signal propagation with context sensitive L-system" << std::endl;
    std::string axiom_cont = "baaadaa";
    std::vector<core::Rule> productions_cont = {
      core::Rule{'b', "a"},
      core::Rule{'a', "b", [](cstr &left, cstr) {return left.ends_with('b');} },
    };

    core::LSystem lsys_cont{ axiom_cont, {}, productions_cont, "" };
    std::cout << "Axiom : " << axiom_cont << std::endl;
    for (int i = 0; i < axiom_cont.length(); i++)
        std::cout << lsys_cont.generate(i) << std::endl;

    std::cout << std::endl;
    /*----------------------------------*/

    std::cout << "Same signal propagation with ignored characters" << std::endl;
    std::string axiom_cont_ignore = "bcdaaccadaaadddaa";
    core::LSystem lsys_cont_ignore{ axiom_cont_ignore, {}, productions_cont, "cd" };
    std::cout << "Axiom : " << axiom_cont_ignore << std::endl;
    for (int i = 0; i < axiom_cont_ignore.length() - 8; i++)
        std::cout << lsys_cont_ignore.generate(i) << std::endl;

    /*----------------------------------*/

    std::srand(std::time(0));

    int height = 1200;
    int width = 1200;

    int base = height - 20;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    LengthController length{[](char) {return 4;}};
    Drawer drawer = Drawer(height, width, starting);
    length = [](char) {
      return 50;
    };

    std::string axiom_cont_test = "F";
    std::vector<core::Rule> productions_cont_test = {
        core::Rule{'F', "FF", [](cstr &left, cstr &right) {return true;}},
        core::Rule{'F', "F[+F]", [](cstr &left, cstr &right) {return left.ends_with("FF");}},
  };
    core::LSystem lsys_cont_test{ axiom_cont_test, {}, productions_cont_test, "+[]" };
    auto tree_cont = lsys_cont_test.generate(5);
    turtle2D(drawer, tree_cont, pi / 8, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("output/context_sensitive/left_example.png");

    return 0;
}
