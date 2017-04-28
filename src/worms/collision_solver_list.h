#ifndef COLLISIONSOLVERLIST_H
#define COLLISIONSOLVERLIST_H

#include "hash_pair.h"

#include <unordered_map>
#include <memory>

namespace worms
{
    struct CollisionSolver;

    class GameObject;

    class CollisionSolverList
    {
        std::unordered_map<std::pair<int, int>, std::unique_ptr<CollisionSolver>, HashPair<int, int>> solvers;

    public:
        CollisionSolverList();
        CollisionSolverList(CollisionSolverList&&) noexcept;
        ~CollisionSolverList();

        CollisionSolverList& operator=(CollisionSolverList&&) noexcept;

        void solve(GameObject& gameObject1, GameObject& gameObject2) const;
    };
}

#endif
