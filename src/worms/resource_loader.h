#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

namespace worms
{
    struct ConfigBlock;

    class Application;

    struct ResourceLoader
    {
        virtual ~ResourceLoader() = default;
        virtual void load(Application& application, const ConfigBlock& block) const = 0;
    };
}

#endif
