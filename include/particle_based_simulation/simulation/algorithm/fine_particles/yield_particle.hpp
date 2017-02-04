//
//  yield_particle.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#ifndef yield_particle_hpp
#define yield_particle_hpp

#include <tuple>
#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle.hpp"

namespace fj {
    struct RheorogyParameter;
    class YieldParticle;
}

class fj::YieldParticle : public fj::DiscritizedParticle<fj::RheorogyParameter>
{
    typedef fj::DiscritizedParticle<fj::RheorogyParameter> Super;
public:
    YieldParticle(const btScalar overlap, const float mass, std::shared_ptr<NormalContainer>& normal, const btScalar rigidRadius)
    : Super(overlap, mass, normal)
    {
        
    }
    
    void addForce(const btVector3& force);
    
    bool hasContactForce()const;
    
    /// first->max, second->min
    const std::pair<btScalar, btScalar>& getMinMax()const;
private:
    
};

#endif /* yield_particle_hpp */
