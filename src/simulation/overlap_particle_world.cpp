//
//  overlap_particle_world.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#include "particle_based_simulation/simulation/overlap_particle_world.hpp"

void fj::OverlapParticleWorld::updateAllObjectsPosition(const btScalar timestep)
{
    // 2DのときはZ方向の力を0にする
    if (m_dimension == Dimension::TwoD)
    {
        auto& objects = m_world->getCollisionObjectArray();
        for (int i = 0; i < objects.size(); i++)
        {
            auto rigidBody = btRigidBody::upcast(objects[i]);
            if (rigidBody)
            {
                btVector3 force = rigidBody->getTotalForce();
                force.setZ(0);
                rigidBody->applyCentralForce(force);
            }
        }
    }
    
    // Bullet Physics はスイープを適用してくれるのでとても安定した位置更新ができる.
    // ここで, stepSimulationの第一引数が更新する時間幅であるが,
    // 第三引数で指定した時間幅まで更新時間が累積しないと位置を更新してくれない.
    // 位置更新を毎フレーム行わせるためには第一引数と第二引数に同じ値を渡さないといけないこのに注意!
    m_world->stepSimulation(timestep, 1/*max substeps*/, timestep);
}

void fj::OverlapParticleWorld::addRigidBody(std::unique_ptr<fj::CollisionObject> body)
{
    getWorldPtr()->addRigidBody(body->getRigidBodyPtr().get());
    m_rigidBody.push_back( std::move(body) );
}

void fj::OverlapParticleWorld::addRigidBody(std::unique_ptr<btRigidBody> btBody)
{
	getWorldPtr()->addRigidBody(btBody.get());
	m_btRigidBody.push_back(std::move(btBody));
}

void fj::OverlapParticleWorld::switchSimulatorDimension(const fj::OverlapParticleWorld::Dimension dimension)
{
    m_dimension = dimension;
}
