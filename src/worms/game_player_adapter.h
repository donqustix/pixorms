#ifndef GAMEPLAYERADAPTER_H
#define GAMEPLAYERADAPTER_H

namespace worms
{
    namespace gui_states
    {
        class Game;
    }

    struct Camera;

    class Worm;

    class GamePlayerAdapter
    {
        gui_states::Game* game;

    public:
        explicit GamePlayerAdapter(gui_states::Game* game) noexcept : game{game} {}

        void setWeapon(int type) const noexcept;
        void useWeapon() const;
        void moveWorm(unsigned delta, bool side) const noexcept;
        void rotateWormDirection(unsigned delta, bool side) const noexcept;
        void punch(float nx, float ny, float flySpeed) const noexcept;

        const Camera& getCamera() const noexcept;
        const Worm* getWorm() const noexcept;
    };
}

#endif
