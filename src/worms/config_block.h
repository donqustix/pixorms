#ifndef CONFIGBLOCK_H
#define CONFIGBLOCK_H

#include <string>
#include <map>

namespace worms
{
    struct ConfigBlock
    {
        std::map<std::string, ConfigBlock> blocks;
        std::map<std::string, std::string> variables;
    };
}

#endif
