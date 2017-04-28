#ifndef COLLISIONSOLVERLANDSCAPEBULLET_H
#define COLLISIONSOLVERLANDSCAPEBULLET_H

#include "worms/collision_solver.h"

namespace worms
{
    namespace collision_solvers
    {
        struct LandscapeBullet;
    }

    struct collision_solvers::LandscapeBullet : CollisionSolver
    {
        void solve(GameObject& gm1, GameObject& gm2) const override;
    };   
}

#endif
