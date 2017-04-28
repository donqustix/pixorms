#ifndef RESOURCECONTAINER_H
#define RESOURCECONTAINER_H

#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <memory>
#include <string>

namespace worms
{
    struct Resource;

    class ResourceContainer
    {
        std::unordered_map<std::string, std::unique_ptr<Resource>> resources;

    public:
        ResourceContainer();
        ResourceContainer(ResourceContainer&&) noexcept;
        ~ResourceContainer();

        ResourceContainer& operator=(ResourceContainer&&) noexcept;

        template<typename T, typename... Args>
        void insert(std::string name, Args&&... args)
        {
            if (resources.find(name) != resources.cend())
                throw std::runtime_error{"there is already the resource " + name};
            resources.emplace(std::move(name), std::make_unique<T>(std::forward<Args>(args)...));
        }

        template<typename T>
        T* find(const std::string& name)
        {
            const auto iter = resources.find(name);
            if (iter == resources.cend())
                throw std::runtime_error{"there is no the " + name + " resource"};
            return dynamic_cast<T*>(iter->second.get());
        }
    };
}

#endif
