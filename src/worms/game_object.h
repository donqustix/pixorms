#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

namespace worms
{
    struct Camera;

    class Graphics;

    class GameObject
    {
    public:
        enum Types
        {
            LANDSCAPE, BULLET, WORM, PARTICLE
        };

    private:
        Types type;

    public:
        explicit GameObject(Types type) noexcept : type{type} {}
        virtual ~GameObject() = default;

        virtual void update(unsigned delta) = 0;
        virtual void render(Graphics& graphics, const Camera& camera) = 0;
        
        virtual bool isKilled() const noexcept = 0;

        auto getType() const noexcept {return type;}
    };
}

#endif
