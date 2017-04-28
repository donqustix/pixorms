#ifndef CONFIG_H
#define CONFIG_H

#include "utility.h"

#include <algorithm>
#include <istream>
#include <utility>
#include <map>

namespace worms
{
    class Config
    {
        struct Block
        {
            std::map<std::string, Block>       blocks;
            std::map<std::string, std::string> variables;
        };

        Block mainBlock;

        template<typename CharT>
        void initialize(std::basic_istream<CharT>& stream, Block& block)
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
                        auto newBlockName = line.substr(1, line.length() - 1);
                        Block newBlock;
                        initialize(stream, newBlock);
                        block.blocks.emplace(std::move(newBlockName), std::move(newBlock));
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

        const Block& findBlock(const std::string& route) const;
        const std::string& findRawValue(const Block& block, const std::string& key) const;

    public:
        static Config parseFile(const std::string& filepath);

        template<typename CharT>
        explicit Config(std::basic_istream<CharT>& stream)
        {
            initialize(stream, mainBlock);
        }

        template<typename T>
        T findValue(const std::string& key, const std::string& route) const
        {
            return utility::convert<T>(findRawValue(findBlock(route), key));
        }

        template<typename T>
        T findValue(const std::string& key) const
        {
            return utility::convert<T>(findRawValue(findBlock(""), key));
        }

        template<typename T>
        T findValue(const std::string& key, const Block& block) const
        {
            return utility::convert<T>(findRawValue(block, key));
        }

        const auto& getMainBlock() const noexcept {return mainBlock;}
    };

    template<>
    inline std::string Config::findValue(const std::string& key, const std::string& route) const
    {
        return findRawValue(findBlock(route), key);
    }

    template<>
    inline std::string Config::findValue(const std::string& key) const
    {
        return findRawValue(findBlock(""), key);
    }

    template<>
    inline std::string Config::findValue(const std::string& key, const Block& block) const
    {
        return findRawValue(block, key);
    }
}

#endif
