//
//  overlap_particle.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#include "particle_based_simulation/simulation/collision_object/particle/overlap_particle.hpp"

const btVector3& fj::OverlapParticle::getPosition()const
{
    return getWorldTransform().getOrigin();
}

void fj::OverlapParticle::setPosition(const btVector3 &position)
{
    btTransform trans(getWorldTransform());
    trans.setOrigin(position);
    setWorldTransform(trans);
}

btScalar fj::OverlapParticle::getOverlapRange()const
{
    return static_cast<const fj::OverlapParticleShape*>(getCollisionShape())->getRadius();
}
