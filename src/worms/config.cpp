#include "config.h"

#include <stdexcept>
#include <fstream>

using worms::ConfigBlock;
using worms::Config;

Config Config::parseFile(const std::string& filepath)
{
    std::ifstream stream{filepath, std::ios::in};
    if (!stream)
        throw std::runtime_error{"config " + filepath + " reading error"};
    return Config{stream};
}

const ConfigBlock& Config::findConfigBlock(const std::string& route) const
{
    if (route.empty()) return mainConfigBlock;

    std::istringstream sstream{route};
    std::string blockName;

    std::getline(sstream, blockName, ':');

    auto iter = mainConfigBlock.blocks.find(blockName);
    for (; std::getline(sstream, blockName, ':'); iter = iter->second.blocks.find(blockName));

    return iter->second;
}

const std::string& Config::findRawValue(const ConfigBlock& block, const std::string& key) const
{
    auto iter = block.variables.find(key);
    if (iter == block.variables.cend())
        throw std::runtime_error{"there is no the variable key " + key};
    return iter->second;
}

