//
//  sph.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/23.
//
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <functional>
#include "particle_based_simulation/simulation/algorithm/sph/sph.hpp"

 const float fj::SPH::kGasConstant = 1;

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
        computePressureTerm(pair);
        computeViscosityTerm(pair);
    }
    
    for (auto& particle : getWorldPtr()->getParticles())
    {
        const auto& kParameter = particle->getParameter();
        particle->applyCentralForce(kParameter.Pressure + kParameter.Viscosity);
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

void fj::SPH::computePressureTerm(const ParticlesContactInfo &contactInfo)
{
    // Spikyカーネル
    const auto Spiky = [](const float r, const float h){
        return -45 * (std::pow(h-r, 2)) / (M_PI * std::pow(h, 6));
    };
    
    auto particle1 = contactInfo.Particle1;
    auto particle2 = contactInfo.Particle2;
    const auto& kDirection12 = contactInfo.kDirection12;
    const auto kDirection21 = -kDirection12;
    const auto h = particle1->getOverlapRange();
    const auto r = contactInfo.kDistance;

    const auto p1 = kGasConstant * (particle1->getParameterPtr()->Density - getDensity());
    const auto p2 = kGasConstant * (particle2->getParameterPtr()->Density - getDensity());
    
    // 共通の数値は計算しておく
    const auto kCoefficient = (p1 + p2) * Spiky(r, h);

    particle1->getParameterPtr()->Pressure += kDirection12
    * particle2->getMass()
    * 0.5 * particle2->getParameter().InverseDensity
    * kCoefficient;
    
    particle2->getParameterPtr()->Pressure += kDirection21
    * particle1->getMass()
    * 0.5 * particle1->getParameter().InverseDensity
    * kCoefficient;
}

void fj::SPH::computeViscosityTerm(const ParticlesContactInfo &contactInfo)
{

}

float fj::SPH::getDensity()const
{
    return m_density;
}

void fj::SPH::setDensity(const float density)
{
    m_density = density;
}
