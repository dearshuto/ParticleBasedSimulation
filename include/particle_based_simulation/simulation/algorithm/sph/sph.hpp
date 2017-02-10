//
//  sph.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/23.
//
//

#ifndef sph_hpp
#define sph_hpp

#include "particle_based_simulation/simulation/algorithm/general/general_particle_algorithm.hpp"

namespace fj {
    struct SPHParameter;
    typedef fj::Particle<SPHParameter> SPHParticle;
    class SPH;
}

struct fj::SPHParameter
{
    float Density;
    float InverseDensity;
    float ViscosityCoefficient;
    btVector3 Pressure;
    btVector3 Viscosity;
};

class fj::SPH : public fj::GeneralParticleAlgorithm<fj::SPHParticle>
{
    typedef fj::GeneralParticleAlgorithm<fj::SPHParticle> Super;
    typedef fj::Particle<fj::SPHParameter> SPHParticle;
public:
    SPH() = default;
    virtual~SPH() = default;
    
private:
    void initializeProperty();
    
    void updateParticleDensity();
    
    void applyForce();
    
    void accumulateParticleForce()override;
    
    void computePressureTerm(const ParticlesContactInfo& contactInfo);
    
    void computeViscosityTerm(const ParticlesContactInfo& contactInfo);
    
public:
    float getDensity()const;
    void setDensity(const float density);
    
    static const float kGasConstant;
private:
    float m_density;
};

#endif /* sph_hpp */
