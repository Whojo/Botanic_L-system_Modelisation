#include <iostream>
#include <optional>

#include "core/l_system.hpp"
#include "utils/turtle.hpp"


using namespace std::string_literals;

namespace
{
    core::State select_randomly(const std::vector<core::State> &states)
    {
        return states[std::rand() % states.size()];

    }
    float get_value_with_chaos(const float &value, const float &chaos)
    {
        if (chaos == 0)
          return value;
    
        const auto per_cent_chaos = chaos * 100;
        const auto per_cent_chaos_variation = std::rand() % (int) (2 * per_cent_chaos);
        const auto variation = per_cent_chaos_variation / 100.0f - chaos;
    
        return value * (1 + variation);
    }
} // namespace


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

// `angle_chaos` and `length_chaos` are pourcentage of allowed variation on,
// respectively the default angle and length
// e.g. an `angle_chaos` = 0.20 will allow a 20% variation of the angle
// both positively and negatively
void chaos_turtle(Drawer &drawer, core::State sentence, double angle,
            LengthController length_controller,
            Palette palette = [](const char) -> Scalar { return {0, 0, 0};},
            const int thickness = 2,
            const float angle_chaos = 0,
            const float length_chaos = 0)
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
                drawer.add_angle(get_value_with_chaos(((params.size() == 0) ? angle : params[0]),
                                 angle_chaos));
                break;
            case '-':
                drawer.add_angle(get_value_with_chaos(((params.size() == 0) ? -angle : -params[0]),
                                 angle_chaos));
                break;
            case '[':
                drawer.push_state();
                break;
            case ']':
                if (!drawer.pop_state())
                    std::cerr << "Empty pop" << std::endl;
                break;
            default:
                drawer.draw_line(
                    palette(c), ((params.size() < 2) ? thickness : params[1]),
                    get_value_with_chaos(((params.size() == 0)
                                              ? length_controller(c)
                                              : params[0]),
                                         length_chaos));
            }
    }
}

int main() {
    int height = 2000;
    int width = 2000;

    int base = height - 100;
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

    drawer = Drawer(height, width, {100., base * 1.}, 0.);
    // define //
    double c = 1;
    double p = 0.3;
    double q = c - p;
    double h = std::pow((p*q),0.5);
    // define //

    double x = 60;
    double t = 0;
    core::State axiom = std::vector<core::Module>{{'F', {x, t}}};
    std::vector<core::Rule> productions_cs = {
      core::Rule{[&](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('F' != pred_.letter)
                return std::nullopt;
            if (0 == pred_.params[1])
                return std::nullopt;
            return core::State{{
              core::Module{'F', {x * p, 2}},
              core::Module{'+', {}},
              core::Module{'F', {x*h, 1}},
              core::Module{'-', {}},
              core::Module{'-', {}},
              core::Module{'F', {x*h, 1}},
              core::Module{'+', {}},
              core::Module{'F', {x * q, 0}},
          }};
      }},
      core::Rule{[&](const core::Module &pred_, const core::State &, const core::State &)
    -> std::optional<core::State> {
            if ('F' != pred_.letter)
                return std::nullopt;
            if (pred_.params[1] > 0)
                return std::nullopt;
            return core::State{{
              core::Module{'F', {x, t - 1}}
          }};
      }}
    };

    core::LSystem lsys{ axiom, {},productions_cs };

    auto generated = lsys.generate(7);

    turtle(drawer, generated, pi / 2.09, length);
    drawer.write_img("output/parametric/forest_example.png");


    // drawer = Drawer("images/Background3.jpg", {5000, 2750});
    double l = 150;
    double thickness = 90;
    core::State axiom_g = std::vector<core::Module>{
      {'T', {l, thickness}},
      {'[', {}},
      {'+', {}},
      {'G', {l, thickness / 1.5f}},
      {']', {}},
      {'[', {}},
      {'-', {}},
      {'-', {}},
      {'H', {l, thickness / 1.5f}},
      {']', {}}
    };
    // ** Alphabet **
    // F: Trunc base
    // L: Left branch
    // R: Right branch
    // G: Left leaves
    // H: Right leaves
    // const auto succ_g = std::vector<core::State>{"L[+G][-H]"s, "L[+G]"s};
    // const auto succ_f = std::vector<core::State>{"R[+G][-H]"s, "R[-H]"s};
    std::vector<core::Rule> productions_g_trunc = {
      core::Rule{[=](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('F' != pred_.letter)
                return std::nullopt;
            const auto t = pred_.params[1]; // Thickness
            return std::vector<core::Module>{
              {'F', {l, t}},
              {'[', {}},
              {'+', {}},
              {'L', {l, t / 1.5f}},
              {']', {}},
              {'[', {}},
              {'-', {}},
              {'-', {}},
              {'R', {l, t / 1.5f}},
              {']', {}}
          };
      }},

      core::Rule{[=](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('G' != pred_.letter)
                return std::nullopt;
            const auto t = pred_.params[1]; // Thickness
            return select_randomly({std::vector<core::Module>{
                {'L', {l, t}},
                {'[', {}},
                {'+', {}},
                {'G', {l, t / 1.5f}},
                {']', {}},
                {'[', {}},
                {'-', {}},
                {'-', {}},
                {'H', {l, t / 1.5f}},
                {']', {}}
              },
              std::vector<core::Module>{
                {'L', {l, t}},
                {'[', {}},
                {'+', {}},
                {'G', {l, t / 1.5f}},
                {']', {}},
              }
            });
      }},

      core::Rule{[=](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('H' != pred_.letter)
                return std::nullopt;
            const auto t = pred_.params[1]; // Thickness
            return select_randomly({std::vector<core::Module>{
                {'R', {l, t}},
                {'[', {}},
                {'+', {}},
                {'G', {l, t / 1.5f}},
                {']', {}},
                {'[', {}},
                {'-', {}},
                {'-', {}},
                {'H', {l, t / 1.5f}},
                {']', {}}
              },
              std::vector<core::Module>{
                {'R', {l, t}},
                {'[', {}},
                {'-', {}},
                {'-', {}},
                {'H', {l, t / 1.5f}},
                {']', {}},
              }
            });
      }}
      // core::Rule{'F', "F[+L][--R]"s},
      // core::Rule{'G', succ_g },
      // core::Rule{'H', succ_f },
    };

    core::LSystem lsys_trunc{ axiom_g, productions_g_trunc };
    auto trunc = lsys_trunc.generate(5);

    // core::LSystem lsys_tree{ trunc, productions_leaves };
    // auto tree = lsys_tree.generate(3);

    Turtle3 turtle(pi / 15);
    std::vector<std::vector<size_t>> faces;
    std::vector<double> thicknesses;
    auto pts = turtle.compute(trunc, "'!{ASL}", faces, thicknesses);
    turtle.to_cylinder(0.1, 8, pts, faces, thicknesses);
    turtle.create_obj_file("output/3d/thickness_param.obj", pts, faces, std::nullopt);

    //turtle(drawer, trunc, pi / 15, length, [](const char) -> Scalar {return {1, 6, 15};}, 90, 0.4, 0.4);
    //drawer.write_img("output/parametric/g_example.png");

    return 0;
}
