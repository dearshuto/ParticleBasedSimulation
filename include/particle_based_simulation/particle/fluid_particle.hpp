//
//  fluid_particle.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef fluid_particle_hpp
#define fluid_particle_hpp

#include "particle.hpp"

namespace shkm {
    class FluidParticle;
}

class shkm::FluidParticle : public shkm::Particle<int>
{
public:
    FluidParticle() = default;
    ~FluidParticle() = default;
};

#endif /* fluid_particle_hpp */
