//
//  mohr_stress_circle_profile.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/27.
//
//

#include <iostream>
#include <fstream>
#include <string>
#include "particle_based_simulation/additional/profile/mohr_stress_circle_profile.hpp"
#include "particle_based_simulation/simulation/general_particle_world.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"

void fj::MohrStressCircleProfile::startSimulationProfile(const fj::Algorithm& algorithm)
{
    
}

void fj::MohrStressCircleProfile::endSimulationProfile(const fj::Algorithm& algorithm)
{
    // 必ずインクリメントできるように先頭に配置する
    static unsigned int frameCount = -1;
    frameCount++;
    
    std::function<double()> func;
    
    const auto& world = getRheorogyAlgorithm().getWorld();

    for (int i = 0; i < world.getParticles().size(); i++)
    {
        // フィルターにかける
        if (m_filterFunction)
        {
            if ( !m_filterFunction(i) )
            {
                continue;
            }

        }
        
        
        const std::string kFilename = "./particle" + std::to_string(i) + "_" + std::to_string(frameCount);
        std::ofstream output(kFilename + ".gnuplot");
        
        if (output.fail())
        {
            std::cout << "MohrStressCircleProfile not run" << std::endl;
            break;
        }
        
        const auto& particle = world.getParticles()[i];
        const auto& kMohrStressCircle = particle->getParameter().MohrStressCircle;
        const auto& kWarrenSpringParameter = particle->getParameter().WarrenSpringCurve;

        const auto kCenter = kMohrStressCircle.getCenter();
        const auto kRadius = kMohrStressCircle.getRadius();
        
        output << "reset" << std::endl;
        output << "set parametric" << std::endl;
        output << "set terminal png" << std::endl;
        output << "set ytics 1.0" << std::endl;
        output << "set size ratio 1.0 1.0" << std::endl;
        output << "set output \"" << kFilename << ".png\"" << std::endl;
        output << "set grid" << std::endl; //gridを表示させる
        output << "unset border; set xtics axis; set ytics axis; set zeroaxis ls -1;" << std::endl;  //軸を交差させる
        output << "set xrange[-3:8]" << std::endl;
        output << "set yrange[-3:8]" << std::endl;
        output << "set trange[-3:8]" << std::endl;

        // ワーレン・スプリング線を描画. 媒介変数を使用するときはまとめて書かないといけないらしい
        output << "plot cos(t)*" << kRadius <<  "+" << kCenter.X << "," << kRadius << "*sin(t), t, " << kWarrenSpringParameter.getParameter().Adhesion << "*(" << "(t+" << kWarrenSpringParameter.getParameter().Collapsibility << ")/" << kWarrenSpringParameter.getParameter().Collapsibility << ")**(1.0/ " << kWarrenSpringParameter.getParameter().SheerIndex << ")" << std::endl;
    }
    
}

void fj::MohrStressCircleProfile::terminate()
{
    
}

std::string fj::MohrStressCircleProfile::getDataAsString()const
{
    return "";
}
