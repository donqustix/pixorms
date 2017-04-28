#ifndef COLLISIONSOLVERLANDSCAPEWORM_H
#define COLLISIONSOLVERLANDSCAPEWORM_H

#include "worms/collision_solver.h"

namespace worms
{
    namespace collision_solvers
    {
        struct LandscapeWorm;
    }

    struct collision_solvers::LandscapeWorm : CollisionSolver
    {
        void solve(GameObject& gm1, GameObject& gm2) const override;
    };  
}

#endif
