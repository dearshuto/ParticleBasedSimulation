//
//  collision_dispatcher.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef collision_dispatcher_hpp
#define collision_dispatcher_hpp

#include <vector>

namespace shkm {
    template<class Particle> class CollisionDispatcher;
}

template<class Particle>
class shkm::CollisionDispatcher
{
    struct ContactParticlePair
    {
        Particle* particle1;
    };
public:
    CollisionDispatcher() = default;
    virtual~CollisionDispatcher() = default;
    
    const ContactParticlePair& getContactParticlePair(const size_t index);
};

#endif /* collision_dispatcher_hpp */
