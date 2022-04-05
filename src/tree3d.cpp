#include "utils/turtle.hpp"
#include "core/l_system.hpp"

int main()
{
    // std::string axiom = "P";
    // 
    // std::vector<core::Rule> productions_param = {
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('P' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'I'}, '+',
    //             '[', 'P', '+', 'F', ']', '-', '-', '/', '/',
    //             '[', '-', '-', 'L', ']', 'I', '[', '+', '+', 'L' ,']' ,'-',
    //             '[', 'P', 'F', ']', '+', '+', 'P', 'F',
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('I' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'F'},
    //             'S','[','/','/','&','&', 'L', ']',
    //             '[','/','/','^','^', 'L', ']', 'F', 'S',
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('S' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'S'},
    //             core::Module{'F'},
    //             core::Module{'S'},
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('L' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'['},
    //             '+', 'f', '-', 'f', 'f', '-', 'f', '+', '|',
    //             '+', 'f', '-', 'f', 'f', '-', 'f', 
    //             ']',
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('F' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'['},
    //             '&', '&', '&', 'G', '/',
    //             'W', '/', '/', '/', '/',
    //             'W', '/', '/', '/', '/',
    //             'W', '/', '/', '/', '/',
    //             'W', '/', '/', '/', '/', 'W',
    //             core::Module{']'},
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('G' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'F'},
    //             core::Module{'F'},
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('W' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'['},
    //             '^', 'F', ']',
    //             '[', '&', '&', '&', '&',
    //             '-', 'f', '+', 'f', '|', '-','f', '+', 'f',
    //             core::Module{']'},
    //       }};
    //   }},
    // };
    // core::LSystem lsys_param{ axiom, productions_param };
    // auto generated = lsys_param.generate(5);
    // Turtle3 turtle_flower(pi / 10);
    // std::vector<std::vector<size_t>> faces_flower;
    // auto pts = turtle_flower.compute(generated, "PISLGW", faces_flower);
    // turtle_flower.create_obj_file("output/3d/flower.obj", pts, faces_flower);

    // std::string axiom_test = "F";
    // 
    // std::vector<core::Rule> productions = {
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('F' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //             core::Module{'F'},
    //             '[', '+', 'F', ']', '[', '-', '\\', 'F', ']','[', '/', 'F', ']',
    //       }};
    //   }},
    // };
    // core::LSystem lsys{ axiom_test, productions };
    // auto state = lsys.generate(2);
    // std::cout << state.get_letters() << std::endl;
    // Turtle3 turtle(pi / 4);
    // std::vector<std::vector<size_t>> faces;
    // auto pts_test = turtle.compute(state, "", faces);
    // turtle.create_obj_file("output/3d/test.obj", pts_test, faces);


    std::string axiom = "A";
    std::vector<core::Rule> productions_bush = {
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('A' != pred_.letter)
                return std::nullopt;
            return core::State{"[&FL!A]/////'[&FL!A]///////'[&FL!A]"};
      }},
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('F' != pred_.letter)
                return std::nullopt;
            return core::State{"S/////F"};
      }},
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('S' != pred_.letter)
                return std::nullopt;
            return core::State{"FL"};
      }},
      core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
        -> std::optional<core::State> {
            if ('L' != pred_.letter)
                return std::nullopt;
            return core::State{"['''^^{-f+f+f-|-f+f+f}]"};
      }},
    };
    core::LSystem lsys_bush{ axiom, productions_bush };
    auto generated = lsys_bush.generate(1);
    Turtle3 turtle_bush(pi / 8);
    std::vector<std::vector<size_t>> faces_bush;
    auto pts_bush = turtle_bush.compute(generated, "'!{ASL}", faces_bush);
    turtle_bush.create_obj_file("output/3d/bush.obj", pts_bush, faces_bush);
    
    return 0;
}
