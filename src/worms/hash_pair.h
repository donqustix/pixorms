#ifndef HASHPAIR_H
#define HASHPAIR_H

#include "utility.h"

#include <utility>

namespace worms
{
    template<typename A, typename B>
    struct HashPair
    {
        std::size_t operator()(const std::pair<A, B>& pair) const noexcept
        {
            std::size_t value = 0;
            worms::utility::hash_combine(value, pair.first);
            worms::utility::hash_combine(value, pair.second);
            return value;
        }
    };
}

#endif
