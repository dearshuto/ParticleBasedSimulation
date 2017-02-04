//
//  cubic_normal_force_container.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#ifndef cubic_normal_force_container_hpp
#define cubic_normal_force_container_hpp

#include <array>
#include <memory>
#include "normal_force_container.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/cube_normal_container.hpp"


namespace fj {
    class CubeNormalForceContainer;
}

class fj::CubeNormalForceContainer : public fj::NormalForceContainer
{
    typedef fj::NormalForceContainer Super;
public:
    CubeNormalForceContainer()
    : Super(fj::CubeNormalContainer::GetInstance())
    , m_pressure({{0.0, 0.0, 0.0}})
    {
        
    }
    
    void addStressAt(const float pressure, const unsigned int index)override;

    void clearStress() override;
    
private:
    std::array<btScalar, 6> m_pressure;
};

#endif /* cubic_normal_force_container_hpp */
