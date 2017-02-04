//
//  discritized_particle_shape.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/10.
//
//

#ifndef discritized_particle_shape_hpp
#define discritized_particle_shape_hpp

#include <memory>
#include <tuple>
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"


class btVector3;
class btMatrix3x3;

namespace fj {
    template<class Parameter> class Particle;
    template<class Parameter> class DiscritizedParticle;
}

class NormalContainer
{
protected:
    NormalContainer() = default;
public:
    virtual~NormalContainer() = default;
    
    /// 面の数
    virtual size_t size()const = 0;
    
    /// i番目に設定されている面の法線.
    virtual const btVector3& get(unsigned int index)const = 0;
};


/** 粉体粒子を離散化した形状を提供する
 * 離散化形状は法線の集合で表される. */
template<class Parameter>
class fj::DiscritizedParticle : public fj::Particle<Parameter>
{
private:
    typedef fj::Particle<Parameter> Super;
public:
    enum class ShapeType
    {
        kCube,
    };
public:
    DiscritizedParticle() = delete;
    virtual~DiscritizedParticle() = default;

    DiscritizedParticle(const btScalar overlap, const btScalar mass, std::shared_ptr<NormalContainer>& normal)
    : Super(overlap, mass)
    {
        
    }
    
    /// 面の数
    size_t size()const
    {
        return m_normal->size();
    }
    
    /// i番目に設定されている面の法線.
    const btVector3& get(unsigned int index)const
    {
        return m_normal->get(index);
    }

private:
    std::shared_ptr<NormalContainer> m_normal;
};

#endif /* discritized_particle_shape_hpp */
