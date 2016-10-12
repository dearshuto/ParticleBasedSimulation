//
//  particle.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef particle_h
#define particle_h

#include <memory>
#include "particle_based_simulation/math/vector3.hpp"

namespace shkm {
    template<class ParticleParameter> class Particle;
}

template <class ParticleParameter>
class shkm::Particle
{
public:
    Particle() = default;
    virtual~Particle() = default;
    
    shkm::Vector3 Position;
    
    ParticleParameter Parameter;
};

#endif /* particle_h */
