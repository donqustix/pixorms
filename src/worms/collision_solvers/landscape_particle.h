#ifndef COLLISIONSOLVERLANDSCAPEPARTICLE_H
#define COLLISIONSOLVERLANDSCAPEPARTICLE_H

#include "worms/collision_solver.h"

namespace worms
{
    namespace collision_solvers
    {
        struct LandscapeParticle;
    }

    struct collision_solvers::LandscapeParticle : CollisionSolver
    {
        void solve(GameObject& gm1, GameObject& gm2) const override;
    };
}

#endif
