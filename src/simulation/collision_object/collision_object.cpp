//
//  collision_object.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/29.
//
//

#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

fj::CollisionObject::CollisionObject(const btScalar mass, std::unique_ptr<btCollisionShape> collisionShape)
{
    init(mass, std::move(collisionShape));
}

void fj::CollisionObject::init(const btScalar mass, std::unique_ptr<btCollisionShape> collisionShape)
{
    m_mass = mass;
    m_motionState.reset(new btDefaultMotionState);
    m_collisionShape = std::move(collisionShape);
    btRigidBody::btRigidBodyConstructionInfo info(mass, m_motionState.get(), m_collisionShape.get());
    m_rigidBody.reset(new btRigidBody{info});

}

void fj::CollisionObject::applyCentralForce(const btVector3 &force)
{
    getRigidBodyPtr()->applyCentralForce(force);
}

const btVector3& fj::CollisionObject::getLinearVelocity()const
{
    return getRigidBody().getLinearVelocity();
}

void fj::CollisionObject::setLinearVelocity(const btVector3 &velocity)
{
    getRigidBodyPtr()->setLinearVelocity(velocity);
}

const btVector3& fj::CollisionObject::getPosition()const
{
    return m_rigidBody->getWorldTransform().getOrigin();
}

void fj::CollisionObject::setPosition(const btVector3 &position)
{
    btTransform transform(m_rigidBody->getWorldTransform());
    transform.setOrigin(position);
    m_rigidBody->setWorldTransform(transform);
}
