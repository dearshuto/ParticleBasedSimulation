//
//  sph.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/23.
//
//

#ifndef sph_hpp
#define sph_hpp

#include "particle_based_simulation/simulation/algorithm/general/particle_algorithm.hpp"

namespace fj {
    struct SPHParameter;
    class SPH;
}

struct fj::SPHParameter
{
    float Density;
    float InverseDensity;
    btVector3 Pressure;
    float Viscosity;
};

class fj::SPH : public fj::ParticleAlgorithm<fj::SPHParameter>
{
    typedef fj::ParticleAlgorithm<fj::SPHParameter> Super;
    typedef fj::Particle<fj::SPHParameter> SPHParticle;
public:
    SPH() = default;
    virtual~SPH() = default;
    
private:
    void initializeProperty();
    
    void updateParticleDensity();
    
    void applyForce();
    
    void accumulateParticleForce()override;
    
    void applyPressureTerm(const ParticlesContactInfo& contactInfo);
    
    void applyViscosityTerm(const ParticlesContactInfo& contactInfo);
};

#endif /* sph_hpp */
