//
//  overlap_particle.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef overlap_particle_hpp
#define overlap_particle_hpp

#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/overlap_particle_shape.hpp"

namespace fj {
    class OverlapParticle;
}

/// オーバーラップ情報が取得できるパーティクル.
/**  */
class fj::OverlapParticle : public fj::CollisionObject
{
protected:
    typedef fj::CollisionObject Super;
    OverlapParticle() = delete;
    /**
     * @param overlap オーバーラップが発生する半径.
     * @param mass 質量[kg].
     * @note 引数で指定したオーバーラップは他の粒子のオーバーラップと衝突することに留意してください.
     *             例えばオーバーラップ0.5で作られたパーティクル同士の衝突を検知するのは, 粒子間の距離が 0.5+0.5→1.0 の時です.*/
    OverlapParticle(const btScalar overlap, const btScalar mass);
public:
    virtual~OverlapParticle() = default;
    
    btScalar getOverlapRange()const;
};

#endif /* overlap_particle_hpp */
