//
//  rheorogy_algorithm.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#ifndef rheorogy_algorithm_hpp
#define rheorogy_algorithm_hpp

#include <memory>
#include "yield_particle.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"
#include "particle_based_simulation/simulation/algorithm/general/particle_algorithm.hpp"

namespace fj {
    class RheorogyAlgorithm;
}

/// レオロジーモデルを利用して粒子間力を計算するアルゴリズム.
/**  */
class fj::RheorogyAlgorithm : public fj::ParticleAlgorithm<fj::YieldParticle>
{
    typedef fj::ParticleAlgorithm<fj::RheorogyParameter> Super;
public:
    RheorogyAlgorithm() = default;
    ~RheorogyAlgorithm() = default;
        
private:
    void accumulateParticleForce()override;
    
    void analyze()override;
    
    void updateParticleState();
    
    void applyNormalComponentContactForce(const ParticlesContactInfo& contactInfo);
    
    void applyTangentialComponentContactForce(const ParticlesContactInfo& contactInfo);
    
    void applyCollisionParticleForce();
    
    btScalar computeDashpodEnvelope(const fj::YieldParticle &particle1, const fj::YieldParticle &particle2)const;
    
    btScalar computeReducedMass(const fj::YieldParticle &particle1, const fj::YieldParticle &particle2)const;
    
    void applyVandeerWaalsForce(const ParticlesContactInfo& contactInfo)const;
};

#endif /* rheorogy_algorithm_hpp */
