#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

namespace worms
{
    class Application;
    class Config;

    namespace resource_loader
    {
        void load(Application& application, const Config& config);
    }
}

#endif
