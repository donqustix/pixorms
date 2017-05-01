#ifndef CONFIG_H
#define CONFIG_H

#include "config_block.h"
#include "utility.h"

#include <algorithm>
#include <istream>
#include <utility>

namespace worms
{
    class Config
    {
        ConfigBlock mainConfigBlock;

        template<typename CharT>
        void initialize(std::basic_istream<CharT>& stream, ConfigBlock& block)
        {
            std::string line;
            while (std::getline(stream, line))
            {
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                switch (line[0])
                {
                    case '/':
                    case '*':
                        return;
                    case '!':
                    {
                        auto newConfigBlockName = line.substr(1, line.length() - 1);
                        ConfigBlock newConfigBlock;
                        initialize(stream, newConfigBlock);
                        block.blocks.emplace(std::move(newConfigBlockName), std::move(newConfigBlock));
                        break;
                    }
                    default:
                    {
                        std::istringstream sstream{line};
                        std::string key, value;
                        std::getline(sstream, key, '=');
                        std::getline(sstream, value);
                        block.variables.emplace(std::move(key), std::move(value));
                        break;
                    }
                }
            }
        }

        const ConfigBlock& findConfigBlock(const std::string& route) const;
        const std::string& findRawValue(const ConfigBlock& block, const std::string& key) const;

    public:
        static Config parseFile(const std::string& filepath);

        template<typename CharT>
        explicit Config(std::basic_istream<CharT>& stream)
        {
            initialize(stream, mainConfigBlock);
        }

        template<typename T>
        T findValue(const std::string& key, const std::string& route) const
        {
            return utility::convert<T>(findRawValue(findConfigBlock(route), key));
        }

        template<typename T>
        T findValue(const std::string& key) const
        {
            return utility::convert<T>(findRawValue(findConfigBlock(""), key));
        }

        template<typename T>
        T findValue(const std::string& key, const ConfigBlock& block) const
        {
            return utility::convert<T>(findRawValue(block, key));
        }

        const auto& getMainBlock() const noexcept {return mainConfigBlock;}
    };

    template<>
    inline std::string Config::findValue(const std::string& key, const std::string& route) const
    {
        return findRawValue(findConfigBlock(route), key);
    }

    template<>
    inline std::string Config::findValue(const std::string& key) const
    {
        return findRawValue(findConfigBlock(""), key);
    }

    template<>
    inline std::string Config::findValue(const std::string& key, const ConfigBlock& block) const
    {
        return findRawValue(block, key);
    }
}

#endif
