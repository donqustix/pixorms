#ifndef LANDSCAPEGENERATORSANDY_H
#define LANDSCAPEGENERATORSANDY_H

#include "worms/landscape_generator.h"

namespace worms
{
    namespace landscape_generators
    {
        class Sandy;
    }

    class ResourceContainer;
    class Surface;

    class landscape_generators::Sandy : public LandscapeGenerator
    {
        const Surface* surface;

    public:
        explicit Sandy(ResourceContainer& resourceContainer);

        void generate(const LandscapeGeneratorAdapter& adapter) const override;
    };
}

#endif
