//
//  collision_object.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/29.
//
//

#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

void fj::CollisionObject::setCollisionShapeWithMemoryManagement(std::unique_ptr<btCollisionShape> collisionShape)
{
    setCollisionShape(collisionShape.get());
    m_collisionShape = std::move(collisionShape);
}
