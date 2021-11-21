#include <iostream>

extern "C" {
namespace Bar {
    void bar() {
        std::cout << "Baaaaaaar!" << std::endl;
    }
}
}