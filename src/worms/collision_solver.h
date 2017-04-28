#ifndef COLLISIONSOLVER_H
#define COLLISIONSOLVER_H

namespace worms
{
    class GameObject;

    struct CollisionSolver
    {
        virtual ~CollisionSolver() = default;

        virtual void solve(GameObject& gameObject1, GameObject& gameObject2) const = 0;
    };
}

#endif
