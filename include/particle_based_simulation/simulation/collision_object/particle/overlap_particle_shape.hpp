//
//  overlap_particle_shape.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/15.
//
//

#ifndef overlap_particle_shape_hpp
#define overlap_particle_shape_hpp

#include <vector>
#include <memory>
#include <btBulletCollisionCommon.h>

namespace fj {
    class OverlapParticleShape;
}

/// Bullet Physicsのフレームワークで使用される形状を粉体粒子用にカスタマイズしたもの.
/** オーバーラップを検出するために利用するので, 形状は球体とします. 
 * 粒子形状はほとんどが同じであるはずなので, できるだけ使いまわしが効くようにしたほうがいい.
 * そこで, このクラスを直接インスタンス化することは禁止し, インスタンス管理の窓口になってもらう.*/
class fj::OverlapParticleShape : public btSphereShape
{
private:
    typedef btSphereShape Super;
    OverlapParticleShape() = delete;
    
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
public:
    virtual~OverlapParticleShape() = default;
    
    /// 指定した半径のインスタンスを取得する
    /**
     * @pre m_shapes が半径順にソートされている. */
    static fj::OverlapParticleShape*const GetParticleShape(const float radius, const float bias = 0.01);
    
private:
    // 新しく要素を追加する. インスタンスはこのクラスの内部で管理されているので, メモリリークは気にしなくていい.
    static fj::OverlapParticleShape*const CreateNewInstance(const float radius);
private:
    static std::vector<std::unique_ptr<fj::OverlapParticleShape>> m_shapes;
};

#endif /* fine_particle_shape_hpp */
