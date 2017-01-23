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
    float Viscosity;
};

class fj::SPH : public fj::ParticleAlgorithm<fj::SPHParameter>
{
    typedef fj::ParticleAlgorithm<fj::SPHParameter> Super;
public:
    SPH() = default;
    virtual~SPH() = default;
    
    void accumulateParticleForce()override;
};

#endif /* sph_hpp */
