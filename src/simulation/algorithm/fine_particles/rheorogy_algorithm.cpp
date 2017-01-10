//
//  rheorogy_algorithm.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#include <numeric>
#include <cmath>
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/collapse_state.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"

void fj::RheorogyAlgorithm::accumulateParticleForce()
{
    auto pairIterator = getWorldPtr()->overlapParticlePairIterator();
    while(pairIterator->hasNext())
    {
        const auto kContactInfo = pairIterator->next();
        const auto particle1 = kContactInfo.Particle1;
        const auto particle2 = kContactInfo.Particle2;
        const auto kRadiusSum = particle1->getParameter().Radius + particle2->getParameter().Radius;
        const bool kIsOverlap = kContactInfo.kDistance < kRadiusSum;
        
        if ( kIsOverlap )
        {
            const auto kOverlap = kRadiusSum - kContactInfo.kDistance;
            
            applyNormalComponentContactForce(kContactInfo, kOverlap);
            applyTangentialComponentContactForce(kContactInfo);
        }
    }
}

void fj::RheorogyAlgorithm::analyze()
{
    for (auto& particle : getWorldPtr()->getParticles())
    {
        // stateにインスタンスが設定されてないので, 必ずぬるぽで落ちる
        const auto& status = particle->getParameter().State;
        status->update(particle.get());
    }
}

void fj::RheorogyAlgorithm::applyNormalComponentContactForce(const ParticlesContactInfo &contactInfo, const btScalar overlap)
{
    constexpr double kPI = 3.141592653589793238462643383279502884;
    auto particle1 = contactInfo.Particle1;
    auto particle2 = contactInfo.Particle2;
    
    const btScalar kSpringK = particle1->getParameter().SpringParameter;
    const btScalar E = 10;
    
    const btVector3 kDirection12 = contactInfo.kNormalizedDirection12;
    const btVector3 kDirection21 = -kDirection12;
    const auto kDistance = contactInfo.kDistance;
    
    // ばね
    particle1->getParameterPtr()->MohrStressCircle.addContactForce(kSpringK * kDistance * kDirection21);
    particle2->getParameterPtr()->MohrStressCircle.addContactForce(kSpringK * kDistance * kDirection12);
    
    // ダッシュポッド
    const btVector3 kRelativeVelocity12 = particle2->getLinearVelocity() - particle1->getLinearVelocity();
    const btVector3 kRelativeVelocity21 = -kRelativeVelocity12;
    const auto kReducedMass = computeReducedMass(std::cref(*particle1), std::cref(*particle2));
    const auto kDashpodEnvelope = computeDashpodEnvelope(*particle1, *particle2);
    
    const auto kEta = -2.0 * kDashpodEnvelope * std::log(E) * std::sqrt(
                                                                        (kReducedMass * kSpringK)
                                                                        / (std::pow(kPI, 2.0) * std::pow(std::log(E), 2.0))
                                                                        );
    
    particle1->getParameterPtr()->MohrStressCircle.addContactForce(kEta * kRelativeVelocity21);
    particle2->getParameterPtr()->MohrStressCircle.addContactForce(kEta * kRelativeVelocity12);
}

btScalar fj::RheorogyAlgorithm::computeDashpodEnvelope(const Particle &particle1, const Particle &particle2)const
{
    const auto& kRheorogyParameter1 = particle1.getParameter();
    const auto& kRheorogyParameter2 = particle2.getParameter();
    
    return (kRheorogyParameter1.DashpodEnvelope + kRheorogyParameter2.DashpodEnvelope) / 2.0;
}

btScalar fj::RheorogyAlgorithm::computeReducedMass(const Particle &particle1, const Particle &particle2)const
{
    const auto kMass1 = particle1.getMass();
    const auto kMass2 = particle2.getMass();
    
    return (kMass1 * kMass2) / (kMass1 + kMass2);
}

void fj::RheorogyAlgorithm::applyVandeerWaalsForce(const ParticlesContactInfo& contactInfo)const
{
    auto particle1 = contactInfo.Particle1;
    auto particle2 = contactInfo.Particle2;
    const btScalar kRadius1 = particle1->getParameter().Radius;
    const btScalar kRadius2 = particle2->getParameter().Radius;
    const btScalar HamakerConstant = 0;
    
    // 粒子の中心間距離
    const btScalar kDistance = contactInfo.kDistance;
    
    // 近傍粒子から受けるファンデルワールス力の方向
    const btVector3 kNormalizedDirection21 = -contactInfo.kNormalizedDirection12;
    const btVector3 kNormalizedDirection12 = contactInfo.kNormalizedDirection12;
    
    // 粒子の表面間距離
    const btScalar kH = std::max(
                                 btScalar(0.000004) //*発散防止のクランプ*/
                                 , kDistance - (kRadius1 + kRadius2)
                                 );
    
    // 換算粒径
    const btScalar kD = (kRadius1 * kRadius2) / (kRadius1 + kRadius2);
    
    const btScalar kF = HamakerConstant * kD / (24 * std::pow(kH, 2.0));
    
    particle1->applyCentralForce(kF * kNormalizedDirection21);
    particle2->applyCentralForce(kF * kNormalizedDirection12);
}

void fj::RheorogyAlgorithm::applyTangentialComponentContactForce(const ParticlesContactInfo &contactInfo)
{
    
}
