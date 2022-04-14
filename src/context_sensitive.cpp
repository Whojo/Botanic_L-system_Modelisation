#include "core/l_system.hpp"
#include "utils/turtle.hpp"

using namespace std::string_literals;

int main()
{
    std::cout << "Signal propagation with context sensitive L-system" << std::endl;
    std::string axiom_cont = "baaadaa";
    std::vector<core::Rule> productions_cont = {
      core::Rule{'b', "a"s},
      core::Rule{'a', "b"s, [](const core::State &left,const core::State&) {
            return left.get_letters().ends_with('b');
            } 
        },
    };

    core::LSystem lsys_cont{ axiom_cont, {}, productions_cont, "" };
    std::cout << "Axiom : " << axiom_cont << std::endl;
    for (int i = 0; i < axiom_cont.length(); i++)
        std::cout << lsys_cont.generate(i).get_letters() << std::endl;

    std::cout << std::endl;
    /*----------------------------------*/

    std::cout << "Same signal propagation with ignored characters" << std::endl;
    std::string axiom_cont_ignore = "bcdaaccadaaadddaa";
    core::LSystem lsys_cont_ignore{ axiom_cont_ignore, {}, productions_cont, "cd" };
    std::cout << "Axiom : " << axiom_cont_ignore << std::endl;
    for (int i = 0; i < axiom_cont_ignore.length() - 8; i++)
        std::cout << lsys_cont_ignore.generate(i).get_letters() << std::endl;

    /*----------------------------------*/

    std::srand(std::time(0));

    int height = 1200;
    int width = 1200;

    int base = height - 20;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    LengthController length{[](char) {return 1;}};
    Drawer drawer = Drawer(height, width, starting);
    length = [](char) {
      return 50;
    };

    std::string axiom_cont_test = "F";
    std::vector<core::Rule> productions = {
        core::Rule{'F', "FF"s},
    };
    std::vector<core::Rule> productions_cont_test = {
        core::Rule{'F', "F[+F]"s, [](const core::State &left, const core::State &right) {
            return left.get_letters().ends_with("FF");
            }
        },
  };
    core::LSystem lsys_cont_test{ axiom_cont_test, productions, productions_cont_test, "+[]" };
    auto tree_cont = lsys_cont_test.generate(7);
    turtle2D(drawer, tree_cont.get_letters(), pi / 8, length, [](char) -> Scalar {return {2, 4, 33};}, 2);
    drawer.write_img("output/context_sensitive/left_example.png");

    return 0;
}
