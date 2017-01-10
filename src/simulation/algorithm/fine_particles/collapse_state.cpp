//
//  collapse_state.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#include <numeric>
#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/collapse_state.hpp"

void fj::CollapseState::update(fj::Particle<fj::RheorogyParameter> *particle)
{
    // 崩壊状態では普通に接触力を適用させる.
    
    const auto force = particle->getParameter().MohrStressCircle.getContactForceContainer();
    const btVector3 kContactForceSum = std::accumulate(std::begin(force), std::end(force), btVector3(0, 0, 0)/*初期値*/);
    particle->applyCentralForce(kContactForceSum);
    particle->getParameterPtr()->MohrStressCircle.clearContactForce();
}
