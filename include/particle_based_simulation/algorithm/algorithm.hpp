//
//  algorithm.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef algorithm_hpp
#define algorithm_hpp

#include "particle_based_simulation/collision_dispatcher/collision_dispatcher.hpp"

namespace shkm {
    template<class Particle> class Algorithm;
}

template<class Particle>
class shkm::Algorithm
{
public:
    Algorithm() = default;
    virtual~Algorithm() = default;
    
    virtual void stepSimulation(const float timestep)  = 0;
    
    virtual void accumulateForce(shkm::CollisionDispatcher<Particle>);
};

#endif /* algorithm_hpp */
