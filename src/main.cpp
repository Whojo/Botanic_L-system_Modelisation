#include <iostream>

#include "core/l_system.hpp"


int main() {
    std::string axiom_ = "b";
    std::vector<core::Rule> productions_ = {
        core::Rule{'a', "ab"},
        core::Rule{'b', "a"}
    };

    core::LSystem lsys{axiom_, productions_};

    auto generated_str = lsys.generate(5);

    std::cout << generated_str << std::endl;

    return 0;
}
