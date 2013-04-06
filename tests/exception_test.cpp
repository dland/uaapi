#include <iostream>
#include <exception>

#include "Exception.h"

int main()
{
    // Uaapi::Exception
    try
    { throw Uaapi::Exception("An exception was thrown."); }
    catch (std::exception& e)
    { std::cout << e.what() << std::endl; }

    // Uaapi::FatalError
    try
    { throw Uaapi::FatalError("An fatal error happened."); }
    catch (std::exception& e)
    { std::cout << e.what() << std::endl; }

    // Uaapi::RuntimeError
    try
    { throw Uaapi::RuntimeError("An runtime error happened."); }
    catch (std::exception& e)
    { std::cout << e.what() << std::endl; }

    return 0;
}
