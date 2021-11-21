#include <iostream>

#include "foo.hpp"

int main() {
    std::cout << "Main" << std::endl;
    foo();
    return 0;
}

// g++ -o main main.cpp foo.cpp  

// g++ -shared -o libmain.so main.cpp foo.cpp
// main works, foo not

// g++ -c main.cpp foo.cpp foo.hpp
// g++ -o main main.o foo.o
// g++ -shared -o libmain.so main.o foo.o


// g++ -shared -o libmain.so main.cpp foo.cpp // works with extern "C" in .hpp and .cpp

// g++ -dynamiclib -flat_namespace -o libmain.so main.cpp foo.cpp // works with extern "C" in .hpp and .cpp

