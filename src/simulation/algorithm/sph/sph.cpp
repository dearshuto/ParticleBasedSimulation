//
//  sph.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/23.
//
//

#include <math.h>
#include <cmath>
#include <functional>
#include "particle_based_simulation/simulation/algorithm/sph/sph.hpp"

void fj::SPH::accumulateParticleForce()
{
    initializeProperty();
    
    updateParticleDensity();
    
    applyForce();
}

void fj::SPH::initializeProperty()
{
    for (auto& particle: getWorldPtr()->getParticles())
    {
        // 密度は自分の質量で初期化
        particle->getParameterPtr()->Density = particle->getMass();
        
        // 圧力は0で初期化
        particle->getParameterPtr()->Pressure = {0.0, 0.0, 0.0};
    }

}

void fj::SPH::applyForce()
{
    auto iterator = getWorldPtr()->overlapParticlePairIterator();
    
    while(iterator->hasNext())
    {
        const auto pair = iterator->next();
        applyPressureTerm(pair);
        applyViscosityTerm(pair);
    }
}

void fj::SPH::updateParticleDensity()
{
    // Poly6 カーネル
    const auto Poly6 = [](const float r, const float h){
        return 315 * std::pow(h*h-r*r, 3) /(64*M_PI*std::pow(h, 9));
    };

    // 近傍粒子から密度を算出する.
    auto iterator = getWorldPtr()->overlapParticlePairIterator();
    while (iterator->hasNext())
    {
        const auto pair = iterator->next();
        const auto& particle1 = pair.Particle1;
        const auto& particle2 = pair.Particle2;
        const auto h = particle1->getOverlapRange();
        const auto r = pair.kDistance;
        
        particle1->getParameterPtr()->Density += particle2->getMass() * Poly6(r, h);
        particle2->getParameterPtr()->Density += particle1->getMass() * Poly6(r, h);
    }
    
    // 密度の逆数を計算しておく
    for (auto& particle: getWorldPtr()->getParticles())
    {
        particle->getParameterPtr()->InverseDensity = 1.0 / particle->getParameterPtr()->Density;
    }

}

void fj::SPH::applyPressureTerm(const ParticlesContactInfo &contactInfo)
{
    // Spikyカーネル
    const auto Spiky = [](const float r, const float h){
        return -45 * (std::pow(h-r, 2)) / (M_PI * std::pow(h, 6));
    };
    
    auto particle1 = contactInfo.Particle1;
    auto particle2 = contactInfo.Particle2;
    const auto h = particle1->getOverlapRange();
    const auto r = contactInfo.kDistance;

    particle1->getParameterPtr()->Pressure += contactInfo.kDirection12
    * particle1->getParameterPtr()->InverseDensity
    * Spiky(r, h);
}

void fj::SPH::applyViscosityTerm(const ParticlesContactInfo &contactInfo)
{

}
