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
    // Bullet Physics はスイープを適用してくれるのでとても安定した位置更新ができる.
    // ここで, stepSimulationの第一引数が更新する時間幅であるが,
    // 第三引数で指定した時間幅まで更新時間が累積しないと位置を更新してくれない.
    // 位置更新を毎フレーム行わせるためには第一引数と第二引数に同じ値を渡さないといけないこのに注意!
    m_world->stepSimulation(timestep, 1/*max substeps*/, timestep);
}

void fj::OverlapParticleWorld::addRigidBody(std::unique_ptr<btRigidBody> body)
{
    getWorldPtr()->addRigidBody(body.get());
    m_rigidBody.push_back( std::move(body) );
}