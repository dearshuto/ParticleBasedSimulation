//
//  profiling_example.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/08/25.
//
//

#include <array>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>
#include <memory>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include "particle_based_simulation/simulation/general_particle_world.hpp"
#include "particle_based_simulation/simulation/algorithm/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"
#include "particle_based_simulation/simulation/collision_object/primitive/box.hpp"
#include "particle_based_simulation/simulation/collision_object/mesh/mesh.hpp"
#include "particle_based_simulation/additional/profile/simulation_time_profile.hpp"
#include "particle_based_simulation/additional/profile/mohr_stress_circle_profile.hpp"
#include "particle_based_simulation/additional/profile/mohr_stress_circle_distribution.hpp"
#include "particle_based_simulation/additional/povray/povray_output.hpp"

int main(int argc, char** argv)
{
    const unsigned int simulationStep = 200;
    fj::RheorogyAlgorithm rheorohyAlgorithm;
    auto world = rheorohyAlgorithm.getWorldPtr();

    world->setGravity( btVector3(0, -9.8, 0) );
    
    std::unique_ptr<btMotionState> meshMotionState(new btDefaultMotionState());
    std::unique_ptr<fj::Mesh> mesh(new fj::Mesh(
                                                btScalar(0.0)/*mass*/
                                                ,std::move(meshMotionState)
                                                ));
    // 読み込んだメッシュの数が返ってくる
    if ( !mesh->loadFromFile("../../asset/bunny.obj") )
    {
        return false;
    }
    mesh->getCollisionShape()->setLocalScaling(btVector3(5, 5, 5));
    world->addRigidBody(std::move(mesh));
    
    
    // 床
    const btScalar mass(0.);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-10,0));
    
    std::unique_ptr<fj::Box> box(new fj::Box(btVector3(100, 10, 100), mass));
    box->setWorldTransform(groundTransform);
    world->addRigidBody( std::move(box));
    

    
    // 粒子生成
    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 1; k++)
            {
                btVector3 position = btVector3(i, j, k);
                position += btVector3(0, 15, 0);
                
                auto particle = fj::RheorogyAlgorithm::GenerateParticle(position);
//                particle->setCollisionShape(&fj::FineParticle::CollisionShape);
                //fj::FineParticle::GenerateFineParticle( fj::DiscritizedParticleShape::ShapeType::kCube, position);
//                particle->getWarrenSpringCurvePtr()->getParameterPtr()->Adhesion = 5.0;
//                particle->getWarrenSpringCurvePtr()->getParameterPtr()->SheerIndex = 5;
                world->addParticle(std::move(particle));
            }
        }
    }
    
    // シミュレーションを進め, かかった時間を出力し, シミュレーション結果をpovray形式で吐き出す
    for (int i = 0; i < simulationStep; i++)
    {
        rheorohyAlgorithm.stepSimulation(1.0/60.0);
        const auto& kPosition = rheorohyAlgorithm.getWorld().getParticles()[0]->getPosition();
        std::cout << kPosition.x() << " " << kPosition.y() << " " << kPosition.z() << std::endl;
    }
    
    rheorohyAlgorithm.terminate();
    
    return 0;
}
