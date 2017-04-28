#include "collision_solver_list.h"
#include "collision_solver.h"
#include "game_object.h"

#include "collision_solvers/landscape_worm.h"
#include "collision_solvers/landscape_bullet.h"
#include "collision_solvers/landscape_particle.h"

using worms::CollisionSolverList;

using worms::collision_solvers::LandscapeWorm;
using worms::collision_solvers::LandscapeBullet;
using worms::collision_solvers::LandscapeParticle;

CollisionSolverList::CollisionSolverList()
{
    solvers.emplace(std::make_pair(GameObject::LANDSCAPE, GameObject::WORM    ), std::make_unique<LandscapeWorm>());
    solvers.emplace(std::make_pair(GameObject::LANDSCAPE, GameObject::BULLET  ), std::make_unique<LandscapeBullet>());
    solvers.emplace(std::make_pair(GameObject::LANDSCAPE, GameObject::PARTICLE), std::make_unique<LandscapeParticle>());
}

CollisionSolverList::CollisionSolverList(CollisionSolverList&&) noexcept = default;

CollisionSolverList::~CollisionSolverList() = default;

CollisionSolverList& CollisionSolverList::operator=(CollisionSolverList&&) noexcept = default;

void CollisionSolverList::solve(GameObject& gameObject1, GameObject& gameObject2) const
{
    const auto iter = solvers.find({gameObject1.getType(), gameObject2.getType()});
    iter->second->solve(gameObject1, gameObject2);
}

