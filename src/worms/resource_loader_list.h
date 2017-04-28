#ifndef RESOURCELOADERLIST_H
#define RESOURCELOADERLIST_H

#include <unordered_map>
#include <string>
#include <memory>

namespace worms
{
    struct ResourceLoader;

    class Application;
    class Config;

    class ResourceLoaderList
    {
        std::unordered_map<std::string, std::unique_ptr<ResourceLoader>> loaders;

    public:
        ResourceLoaderList();
        ResourceLoaderList(ResourceLoaderList&&) noexcept;
        ~ResourceLoaderList();

        ResourceLoaderList& operator=(ResourceLoaderList&&) noexcept;

        void load(Application& application, const Config& config) const;
    };
}

#endif
