//
//  smoothed_particle_hydrodynamics.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef smoothed_particle_hydrodynamics_hpp
#define smoothed_particle_hydrodynamics_hpp

#include "algorithm.hpp"

namespace shkm {
    class SmoothedParticleHydrodynamics;
}

class shkm::SmoothedParticleHydrodynamics : public shkm::Algorithm
{
public:
    SmoothedParticleHydrodynamics() = default;
    virtual~SmoothedParticleHydrodynamics() = default;
    
    void stepSimulation(const float stepSimulation) override;
};

#endif /* smoothed_particle_hydrodynamics_hpp */
