#include <iostream>

#include "Singleton.h"

class TestImpl
{
public:

    TestImpl()
    { std::cout << "Creation" << std::endl; }

    ~TestImpl()
    { std::cout << "Destruction" << std::endl; }

    void sayHello()
    { std::cout << "Hello, world!" << std::endl; }
};

typedef Uaapi::SingletonHolder< TestImpl > Test;

int main()
{
    Test::instance().sayHello();
    return 0;
}
