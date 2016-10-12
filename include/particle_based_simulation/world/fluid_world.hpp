//
//  fluid_world.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef fluid_world_hpp
#define fluid_world_hpp

#include "world_impl.hpp"
#include "particle_based_simulation/algorithm/smoothed_particle_hydrodynamics.hpp"
#include "particle_based_simulation/particle/fluid_particle.hpp"

namespace shkm {
    class FluidWorld;
}

class shkm::FluidWorld
    : public shkm::World<shkm::SmoothedParticleHydrodynamics, shkm::FluidParticle>
{
public:
    FluidWorld() = default;
    virtual~FluidWorld() = default;
};

#endif /* fluid_world_hpp */
