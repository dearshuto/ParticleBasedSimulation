//
//  equipoise_state.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/10.
//
//

#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/equipoise_state.hpp"

void fj::EquipoiseState::update(fj::Particle<fj::RheorogyParameter> *particle)
{
    // 「均衡状態 = 静止摩擦力が働いている」ということなので, 粒子の動きを止める
    particle->setLinearVelocity(btVector3{0.0, 0.0, 0.0});
    particle->getParameterPtr()->MohrStressCircle.clearContactForce();
}
