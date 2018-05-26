#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <iostream>
#include <sstream>

class Debug
{
public:
    template <typename T>
    static void Log(T value)
    {
        std::cout << value << std::endl;
    }
};

#endif
