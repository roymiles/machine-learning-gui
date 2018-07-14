#pragma once

#include <iostream>
#include <sstream>

// [[ deprecated ]] use qDebug() << ... instead
namespace je {

class Debug
{
public:
    template <typename T>
    static void Log(T value)
    {
        std::cout << value << std::endl;
    }
};

} // je
