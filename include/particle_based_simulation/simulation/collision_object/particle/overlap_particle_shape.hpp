//
//  overlap_particle_shape.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/15.
//
//

#ifndef overlap_particle_shape_hpp
#define overlap_particle_shape_hpp

#include <btBulletCollisionCommon.h>

namespace fj {
    class OverlapParticleShape;
}

/// Bullet Physicsのフレームワークで使用される形状を粉体粒子用にカスタマイズしたもの.
/** パーティクルは球体であると仮定します. */
class fj::OverlapParticleShape : public btSphereShape
{
    typedef btSphereShape Super;
public:
    OverlapParticleShape() = delete;
    virtual~OverlapParticleShape() = default;
    
    /** 
     * @param effectRange オーバーラップを検知する範囲. */
     OverlapParticleShape(const btScalar effectRange)
    : Super(effectRange)
    {
        // 独自に追加した衝突形状を表すフラグ
        // 現状ではこの fj::OverlapParticleShape しか独自に追加していないが,
        // もしも他の形状を追加することになったらどうにかしましょう.
        m_shapeType = CUSTOM_POLYHEDRAL_SHAPE_TYPE;
    }
};

#endif /* fine_particle_shape_hpp */
