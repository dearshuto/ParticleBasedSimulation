//
//  box.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/29.
//
//

#ifndef box_hpp
#define box_hpp

#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

namespace fj {
    class Box;
}

class fj::Box : public fj::CollisionObject
{
    typedef fj::CollisionObject Super;
public:
    Box() = delete;
    ~Box() = default;
    
    /** 
     * @param size Width, Height, Depth の値. ピボットはキューブの中心
     * @param mass 質量[kg] */
    Box(const btVector3& size, const btScalar mass)
    : Super(mass, nullptr/*motion state*/, nullptr/*collisionShape*/)
    {
        // btMotionStateとbtCollisionShapeをnullptrのまま親クラスのコンストラクタを読んでいるので,
        // このクラスのコンストラクタ内で必ずインスタンスをセットすること. ちなみにnullptrのまま親コンストラクタを呼ぶのは仕様としてOK.
        
        // btMotionStateのセット
        setMotionStateWithMemoryManagement(
                                           std::unique_ptr<btDefaultMotionState>(new btDefaultMotionState())
                                           );
        
        // btBoxShape（衝突形状）のセット
        std::unique_ptr<btBoxShape> boxShape(new btBoxShape(size));
        setCollisionShapeWithMemoryManagement(std::move(boxShape));
    }
};

#endif /* box_hpp */
