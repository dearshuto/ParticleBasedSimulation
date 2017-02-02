//
//  profiling_example.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/08/25.
//
//

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <string>
#include <memory>
#include "particle_based_simulation/simulation/collision_object/primitive/box.hpp"
#include "particle_based_simulation/simulation//collision_object/particle/particle.hpp"
#include "particle_based_simulation/additional/profile/simulation_time_profile.hpp"
#include "particle_based_simulation/additional/profile/mohr_stress_circle_profile.hpp"
#include "particle_based_simulation/additional/profile/mohr_stress_circle_distribution.hpp"
#include "particle_based_simulation/additional/povray/povray_output.hpp"

int main(int argc, char** argv)
{
    fj::FineParticleWorld world;
    world.setGravity( btVector3(0, -9.8, 0) );

    unsigned int simulationStep = 50;
    // 引数に何かしらが渡ってきたらプロファイル設定をおこなう
    if (1 < argc)
    {
        
        std::vector<std::string> commandOption;
        
        // オプションを全てバラす
        for (int i = 1; i < argc; i++)
        {
            commandOption.push_back( std::string(argv[i]) );
        }
        
        std::vector<std::string>::iterator iterator;
        
        // 出力ディレクトリの設定
        std::string outputDirectory(".");
        iterator = std::find_if(commandOption.begin(), commandOption.end()
                                , [](const std::string& option){
                                    return option == "-output";
                                });
        
        if (commandOption.end() != iterator)
        {
            outputDirectory = *(++iterator);
        }

        // シミュレーション回数
        iterator = std::find_if(commandOption.begin(), commandOption.end()
                                , [](const std::string& option){
                                    return option == "-step";
                                });
        
        if (commandOption.end() != iterator)
        {
            // -step の次に数字が来てるものとする
            try {
                simulationStep = std::stoi( *(++iterator) );
            } catch (const std::exception& e) {
                std::cout << "FUCK" << std::endl;
            }

        }
        
        // シミュレーション時間の最大値, 最小値, 平均を知りたいとき
        iterator = std::find_if(commandOption.begin(), commandOption.end()
                                , [](const std::string& option){
                                    return option == "-min_max_average_time";
                                });

        if (commandOption.end() != iterator)
        {
            auto timeProfile = world.addProfileSystem<fj::SimulationTimeProfile>();
            timeProfile->setOutputDirectory(outputDirectory);
            std::cout << "Min, Max, Average profile" << std::endl;
        }

        // 粒子にかかってる力の差分（モール応力円の半径）の分布が知りたいとき
        iterator = std::find_if(commandOption.begin(), commandOption.end()
                                , [](const std::string& option){
                                    return option == "-distribution";
                                });
        if (commandOption.end() != iterator)
        {
            auto distribution = world.addProfileSystem<fj::MohrStressCircleDistribution>();
            distribution->setGraph(0, 10, 0.25);
            distribution->setOutputDirectory(outputDirectory);
            std::cout << "Stress Distribution" << std::endl;
        }

        
        // 粉体崩壊曲線を見たいとき
        iterator = std::find_if(commandOption.begin(), commandOption.end()
                                , [](const std::string& option){
                                    return option == "-collapse_curve";
                                });
        if (commandOption.end() != iterator)
        {
            // --collapse_curveの次にフィルタ番号が指定されていないといけない
            try {
                const auto filter = std::stoi( *(++iterator) );
                
                auto mohrStressCircleProfile = world.addProfileSystem<fj::MohrStressCircleProfile>();
                mohrStressCircleProfile->setFilter( std::function<bool(const int)>([filter](const int index){return index == filter;} ) );
                mohrStressCircleProfile->setOutputDirectory(outputDirectory);
                std::cout << "Chase at " << filter << std::endl;
            } catch (const std::exception& e)
            {
                std::cout << "-collapse_curve number ← Use Integer" << std::endl;
            }
        }

    }
    
    // 床
    const btScalar mass(0.);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-10,0));
    
    std::unique_ptr<fj::Box> box(new fj::Box(btVector3(100, 10, 100), mass));
    box->setWorldTransform(groundTransform);
    world.addRigidBody( std::move(box));
    world.SpringK = 5;
    
    // 粒子生成
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            for (int k = 0; k < 10; k++)
            {
                btVector3 position = btVector3(i, j, k);
                btMatrix3x3 matrix;

//                matrix.setEulerZYX(45, 45, 45);
//                position = matrix * position;
                position += btVector3(0, 0.6, 0);
                
                std::unique_ptr<fj::FineParticle> particle = fj::FineParticle::GenerateFineParticle( fj::DiscritizedParticleShape::ShapeType::kCube, position);
                particle->getWarrenSpringCurvePtr()->getParameterPtr()->Adhesion = 5.0;
                particle->getWarrenSpringCurvePtr()->getParameterPtr()->SheerIndex = 5;
                world.addParticle(std::move(particle));
            }
        }
    }
    
    // ぶつけてみる
    std::unique_ptr<btCollisionShape> groundShape_(new btSphereShape(1.5));
    btScalar mass_(10.5);
    btVector3 localInertia_(0,0,0);
    btTransform groundTransform_;
    groundTransform_.setIdentity();
    groundTransform_.setOrigin(btVector3(2,12,8));
    std::unique_ptr<btDefaultMotionState> myMotionState_(new btDefaultMotionState(groundTransform_));
    btRigidBody::btRigidBodyConstructionInfo rbInfo_(mass_,myMotionState_.get(),groundShape_.get(),localInertia_);
    std::unique_ptr<btRigidBody> body_(new btRigidBody(rbInfo_));
    body_->setRollingFriction(1);
    body_->setFriction(1);
    world.addRigidBody( std::move(body_));
    
    // シミュレーションを進め, かかった時間を出力し, シミュレーション結果をpovray形式で吐き出す
    for (int i = 0; i < simulationStep; i++)
    {
        world.stepSimulation(1.0/480.0);
    }
    
    world.terminate();
    
    return 0;
}
