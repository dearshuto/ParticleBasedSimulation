//
//  world.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef world_h
#define world_h

#include <memory>
#include <vector>
#include "particle_based_simulation/algorithm/algorithm.hpp"
#include "particle_based_simulation/algorithm/additional/additional_procedure.hpp"
#include "particle_based_simulation/collision_dispatcher/collision_dispatcher.hpp"
#include "particle_based_simulation/math/vector3.hpp"

namespace shkm {
    template<class Algorithm, class Particle> class World;
}

template <class Algorithm, class Particle>
class shkm::World
{
public:
    World() = default;
    virtual~World() = default;
    
    const Particle* generateParticle(const shkm::Vector3& position)
    {
        Particle* particle = new Particle();
        std::unique_ptr<Particle> particlePtr(particle);
        m_particles.push_back( std::move(particlePtr) );
        return particle;
    }
    
    void stepSimulation(const float timestep)
    {
        for (auto& additionalProcedure : m_additionalProcedures)
        {
            additionalProcedure->runBeforeStepSimulation(timestep);
        }
        
        getAlgorithmPtr()->stepSimulation(timestep);
        
        for (auto& additionalProcedure : m_additionalProcedures)
        {
            additionalProcedure->runAfterStepSimulation(timestep);
        }
        
    }
    
    template<class AnotherAlgorithm>
    void resetAlgorithm()
    {
        m_algorithm.reset(new AnotherAlgorithm());
    }
    
    const shkm::Algorithm& getAlgorithm()const
    {
        return *m_algorithm;
    }
protected:
    std::unique_ptr<Algorithm>& getAlgorithmPtr()
    {
        return m_algorithm;
    }
private:
    std::vector<std::unique_ptr<Particle>> m_particles;
    
    std::unique_ptr<Algorithm> m_algorithm;
    
    std::vector<std::unique_ptr<shkm::AdditionalProcedure>> m_additionalProcedures;
    
    shkm::CollisionDispatcher<Particle> m_collisionDispatcher;
};

#endif /* world_h */
