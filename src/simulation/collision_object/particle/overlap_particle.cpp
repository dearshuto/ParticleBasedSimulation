//
//  overlap_particle.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#include "particle_based_simulation/simulation/collision_object/particle/overlap_particle.hpp"

fj::OverlapParticle::OverlapParticle(const btScalar overlap, const btScalar mass)
: Super(mass, std::unique_ptr<fj::OverlapParticleShape>{fj::OverlapParticleShape::GetParticleShape(overlap)})
{

}

btScalar fj::OverlapParticle::getOverlapRange()const
{
    return static_cast<const fj::OverlapParticleShape&>(getCollisionShape()).getRadius();
}
