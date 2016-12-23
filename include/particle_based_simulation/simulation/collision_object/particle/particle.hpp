//
//  particle.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/08/25.
//
//

#ifndef particle_hpp
#define particle_hpp

#include <memory>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "overlap_particle.hpp"

namespace fj {
    template<class Parameter> class Particle;
}

/// ズバリ粒子
/** シミュレーションに必要な任意のパラメータをテンプレート引数として指定できる */
template<class Parameter>
class fj::Particle : public fj::OverlapParticle
{
public:
    typedef Parameter ParameterType;
private:
    typedef fj::OverlapParticle Super;
    typedef fj::Particle<Parameter> Self;
public:
    Particle() = delete;
    virtual~Particle() = default;

    /** @copydoc fj::OverlapParticle::OverlapParticle(const btScalar, const btScalar) */
    Particle(const btScalar overlap, const btScalar mass)
    : Super(overlap, mass)
    {
        // Bullet Physicsに「この物体には独自のアルゴリズムを適用する」と判別させるためのフラグを立てておく
        // 主な利用方法はアップキャスト.
        m_internalType |= btCollisionObject::CO_USER_TYPE;
    }

    
    
    
    //---------- Public Static Functions --------------------------------------------------------------------------------------------------------------------
    
    static std::unique_ptr<Self> GenerateParticle(const btScalar overlap, const btScalar mass, const btVector3& position)
    {
        auto particle = std::unique_ptr<Self>(new Self(overlap, mass));
        particle->setPosition(position);
        return particle;
    }
    
    static Self*const Upcast(btCollisionObject*const object)
    {
        if (object->getInternalType()&btCollisionObject::CO_USER_TYPE)
            return static_cast<Particle*const>(object);
        return nullptr;
    }

    static const Self*const Upcast(const btCollisionObject*const object)
    {
        if (object->getInternalType()&btCollisionObject::CO_USER_TYPE)
            return static_cast<Particle*const>(object);
        return nullptr;
    }

    
    
    
    //---------- Public Getters -------------------------------------------------------------------------------------------------------------------------------
    
    const Parameter& getParameter()const
    {
        return m_parameter;
    }
    
    Parameter* getParameterPtr()
    {
        return &m_parameter;
    }
private:
    /// テンプレート引数に指定できる任意のパラメータ
    Parameter m_parameter;
};

#endif /* particle_hpp */
