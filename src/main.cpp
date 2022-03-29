#include <iostream>

#include "core/l_system.hpp"


using namespace std::string_literals;

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

    return 0;
}
