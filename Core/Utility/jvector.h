#pragma once

#include <qlogging.h> // qFatal

namespace je { namespace utility {

/*
 * This class acts as a container for arbitrary types e.g. JVector<int, double>
 * This is different from a std::vector that only allows one type
 */
template<typename T1, typename T2> // TODO: Use template parameter pack
class JVector
{
public:
    JVector()
    {
    }

    template<typename T>
    T get()
    {
        switch(typeid(T))
        {
        case typeid(T1):
            return t1;
            break;
        case typeid(T2):
            return t2;
            break;
        default:
            qFatal("JVector does not contain an element of this type");
        }
    }

private:
    T1 t1;
    T2 t2;
};

} } // utility, je
