#include "utils/turtle.hpp"
#include "core/l_system.hpp"

int main()
{
    // std::string axiom = "P";

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
    // auto state = lsys.generate(1);
    // // std::cout << state.get_letters() << std::endl;
    // // Turtle3 turtle(pi / 4);
    // Turtle3 turtle(pi / 8);
    // std::vector<std::vector<size_t>> faces;
    // auto pts_test = turtle.compute(state, "", faces);
    // turtle.create_obj_file("output/3d/test.obj", pts_test, faces);


    // std::string axiom_bush = "A";
    // std::vector<core::Rule> productions_bush = {
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('A' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"[&FL!A]/////'[&FL!A]///////'[&FL!A]"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('F' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"S/////F"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('S' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"FL"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('L' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"['''^^{-f+f+f-|-f+f+f}]"};
    //   }},
    // };
    // core::LSystem lsys_bush{ axiom_bush, productions_bush };
    // auto bush = lsys_bush.generate(7);
    // Turtle3 turtle_bush(pi / 8);
    // std::vector<std::vector<size_t>> faces_bush;
    // auto pts_bush = turtle_bush.compute(bush, "'!{ASL}", faces_bush);
    // turtle_bush.create_obj_file("output/3d/bush.obj", pts_bush, faces_bush);

    // std::string axiom_param{"A"};
    // std::vector<core::Rule> productions_param = {
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('A' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //           core::Module{'F', {2}},
    //           core::Module{'[', {}},
    //           core::Module{'+', {}},
    //           core::Module{'A', {}},
    //           core::Module{']', {}},
    //           core::Module{'[', {}},
    //           core::Module{'-', {}},
    //           core::Module{'A', {}},
    //           core::Module{']', {}}
    //       }};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    // -> std::optional<core::State> {
    //         if ('F' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{{
    //           core::Module{'F', {pred_.params[0] * 1.456}}
    //       }};
    //   }}
    // };

    // core::LSystem lsys_param{ axiom_param, productions_param };

    // auto generated_param = lsys_param.generate(10);

    // double pi2 = pi / 2.1; // 85°
    // Turtle3 turtle_param(pi2);
    // std::vector<std::vector<size_t>> faces_param;
    // auto pts_param = turtle_param.compute(generated_param, "", faces_param);
    // turtle_param.create_obj_file("output/3d/param.obj", pts_param, faces_param);
    
    // std::string axiom_hilbert = "A";
    // std::vector<core::Rule> productions_hilbert = {
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('A' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"B-F+CFC+F-D&F^D-F+&&CFC+F+B//"};
    //         // return core::State{"B/F\\CFC\\F/D&F^D/F\\&&CFC\\F\\B--"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('B' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"};
    //         // return core::State{"A&F^CFB^F^D^^/F/D^|F^B|FC^F^A--"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('C' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"};
    //         // return core::State{"|D^|F^B/F\\C^F^A&&FA&F^C\\F\\B^F^D--"};
    //   }},
    //   core::Rule{[](const core::Module &pred_, const core::State &, const core::State &)
    //     -> std::optional<core::State> {
    //         if ('D' != pred_.letter)
    //             return std::nullopt;
    //         return core::State{"|CFB-F+B|FA&F^A&&FB-F+B|FC//"};
    //         // return core::State{"|CFB/F\\B|FA&F^A&&FB/F\\B|FC--"};
    //   }},
    // };
    // 
    // core::LSystem lsys_hilbert{ axiom_hilbert, productions_hilbert };

    // auto generated_hilbert = lsys_hilbert.generate(3);
    // std::cout << generated_hilbert.get_letters() << std::endl;
    // Turtle3 turtle_hilbert(pi / 2);
    // std::vector<std::vector<size_t>> faces_hilbert;
    // // core::State test{"F/F\\FFF\\F/F&F^F/F\\&&FFF\\F\\F--"};
    // auto pts_hilbert = turtle_hilbert.compute(generated_hilbert, "ABCD", faces_hilbert);
    // // auto pts_hilbert = turtle_hilbert.compute(test, "", faces_hilbert);
    // turtle_hilbert.create_obj_file("output/3d/hilbert.obj", pts_hilbert, faces_hilbert);


    // Turtle3 turtle_test_hilbert(pi / 2);
    // std::vector<std::vector<size_t>> faces_test_hilbert;
    // auto pts_test_hilbert = turtle_test_hilbert.compute(core::State{"B&F"}, "", faces_test_hilbert);
    // turtle_test_hilbert.create_obj_file("output/3d/hilbert_test.obj", pts_test_hilbert, faces_test_hilbert);

    Turtle3 turtle_cylinder(0);
    std::vector<std::vector<size_t>> faces_cylinder;
    auto pts_cylinder = turtle_cylinder.compute(core::State{"F"}, "", faces_cylinder);
    turtle_cylinder.to_cylinder(2, 16, pts_cylinder, faces_cylinder);
    turtle_cylinder.create_obj_file("output/3d/cylinder_test.obj", pts_cylinder, faces_cylinder);

    return 0;
}
