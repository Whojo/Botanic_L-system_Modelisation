#include <iostream>

#include "core/l_system.hpp"
#include "utils/turtle.hpp"


using namespace std::string_literals;

void turtle(Drawer &drawer, core::State sentence, double angle,
            LengthController length_controller,
            Palette palette = [](const char) -> Scalar { return {0, 0, 0};},
            const int thickness = 2)
{
    for (const auto &mod : sentence.get_modules())
    {
        char c = mod.letter;
        auto params = mod.params;
        switch(c)
        {
            case 'X':
                break;
            case '+':
                drawer.add_angle((params.size() == 0) ? angle : params[0]);
                break;
            case '-':
                drawer.add_angle((params.size() == 0) ? -angle : -params[0]);
                break;
            case '[':
                drawer.push_state();
                break;
            case ']':
                if (!drawer.pop_state())
                    std::cerr << "Empty pop" << std::endl;
                break;
            default:
                drawer.draw_line(palette(c), thickness,
                                 (params.size() == 0) ? length_controller(c) : params[0]);
        }
    }
}

int main() {
    std::string axiom_ = "b";
    std::vector<core::Rule> productions_ = {
        core::Rule{'a', "ab"s},
        core::Rule{'b', "a"s}
    };

    core::LSystem lsys{axiom_, productions_};

    const auto &generated_state = lsys.generate(5);

    std::cout << "Final result: ";
    for (const auto &mod : generated_state.get_modules())
        std::cout << mod.letter;

    std::cout << std::endl;

    int height = 2000;
    int width = 2000;

    int base = height - 20;
    Point2d starting(width / 2.f, base); // Starting Point of the line

    LengthController length{[](char) {return 4;}};
    Drawer drawer = Drawer(height, width, starting);

    std::string axiom_param{"A"};
    std::vector<core::Rule> productions_param = {
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('A' != pred_.letter)
                return std::nullopt;
            return core::State{{
              core::Module{'F', {20}},
              core::Module{'[', {}},
              core::Module{'+', {}},
              core::Module{'A', {}},
              core::Module{']', {}},
              core::Module{'[', {}},
              core::Module{'-', {}},
              core::Module{'A', {}},
              core::Module{']', {}}
          }};
      }},
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('F' != pred_.letter)
                return std::nullopt;
            return core::State{{
              core::Module{'F', {pred_.params[0] * 1.456}}
          }};
      }}
    };

    core::LSystem lsys_param{ axiom_param, productions_param };

    auto generated_param = lsys_param.generate(10);

    double pi2 = pi / 2.1; // 85°
    turtle(drawer, generated_param, pi2, length);
    drawer.write_img("output/parametric/param_example.png");

    return 0;
}
