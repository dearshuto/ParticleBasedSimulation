//
//  yield_particle.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#include <algorithm>
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/yield_particle.hpp"

void fj::YieldParticle::addForce(const btVector3 &force)
{
    const auto& normalContainer = m_normalForceContainer->getNormalContainerSharedPtr();

    for (size_t i = 0; i < normalContainer->size(); ++i)
    {
        const auto& normal = normalContainer->get(i);
        const auto& kNormalStress = std::max<btScalar>(0, normal.dot(force));
        m_normalForceContainer->addStressAt(kNormalStress, i);
    }
}

void fj::YieldParticle::clearForce()
{
    m_normalForceContainer->clearStress();
}

bool fj::YieldParticle::hasContactForce()const
{
    return true;
}
