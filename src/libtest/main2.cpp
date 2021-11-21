#include <iostream>

#include "foo.hpp"
#include "bar.hpp"


int main() {
    std::cout << "Main" << std::endl;
    foo();
    Bar::bar();
    return 0;
}

// g++ -o main2 main2.cpp foo.cpp bar.cpp 

// g++ -shared -o libmain2.so main2.cpp foo.cpp bar.cpp // works with extern "C" in .hpp and .cpp
// call with dlsym("bar")

