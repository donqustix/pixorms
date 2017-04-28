#ifndef UTILITY_H
#define UTILITY_H

#include <functional>
#include <sstream>
#include <string>

namespace worms
{
    namespace utility
    {
        template<typename T>
        T convert(const std::string& str)
        {
            std::istringstream sstream{str};
            T temp;
            sstream >> temp;
            return temp;
        }

        template<typename T>
        inline void hash_combine(std::size_t& seed, const T& v) noexcept
        {
            seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    }
}

#endif
