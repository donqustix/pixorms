#ifndef LANDSCAPEGENERATOR_H
#define LANDSCAPEGENERATOR_H

namespace worms
{
    class LandscapeGeneratorAdapter;

    struct LandscapeGenerator
    {
        virtual ~LandscapeGenerator() = default;
        virtual void generate(const LandscapeGeneratorAdapter& adapter) const = 0;
    };
}

#endif
