//
//  normal_force_container.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#ifndef normal_force_container_hpp
#define normal_force_container_hpp

#include <memory>
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle.hpp"

namespace fj {
    class NormalForceContainer;
}

/// fj::NormalContainer とあわせて使用する.
class fj::NormalForceContainer
{
public:
    NormalForceContainer() = delete;
    virtual~NormalForceContainer() = default;

    NormalForceContainer(std::shared_ptr<fj::NormalContainer> normal)
    : m_normal(normal)
    {
        
    }

    virtual void addStressAt(const float pressure, const unsigned int index) = 0;
    
    virtual void clearStress() = 0;
    
    std::shared_ptr<fj::NormalContainer>& getNormalContainerSharedPtr()
    {
        return m_normal;
    }
    
    virtual std::pair<btScalar, btScalar> getMinMax()const = 0;
private:
    std::shared_ptr<fj::NormalContainer> m_normal;
};

#endif /* normal_force_container_hpp */
