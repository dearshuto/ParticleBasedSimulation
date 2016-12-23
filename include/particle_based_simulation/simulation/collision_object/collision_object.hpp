//
//  collision_object.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/29.
//
//

#ifndef collision_object_hpp
#define collision_object_hpp

#include <memory>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace fj {
    class CollisionObject;
}

/// Bullet Physics のフレームワークの中でシミュレーション可能な物体.
/** シミュレーションしたいオブジェクトは, すべてこのクラスの派生であるべき. */
class fj::CollisionObject : public btRigidBody
{
    typedef btRigidBody Super;
public:
    CollisionObject() = delete;
    virtual~CollisionObject() = default;
    
    /**
     * @param mass 質量[kg]
     * @param motionState Bullet Physicsが提供するオブジェクトの位置情報を管理するクラス. このコンストラクタがを呼ぶ段階でnullptrであっても問題ない. ただしインスタンス化したあとで値をセットしないとぬるぽで落ちる
     * @param collisionShape Bullet Physicsの衝突判定で使用される形状. このコンストラクタを呼ぶ段階でnullptrであっても問題ない. ただしインスタンス化したあとで値をセットしないとぬるぽエラーで落ちる
     * @param localInertia 各軸まわりにおける回転のしやすさ. ゼロベクトルの場合, 回転運動が起きなくなる. デフォルトでは回転しないように設定してある*/
    CollisionObject(const btScalar mass, std::unique_ptr<btMotionState> motionState, std::unique_ptr<btCollisionShape> collisionShape, const btVector3& localInertia = btVector3(0, 0, 0))
    : Super(mass, motionState.get(), collisionShape.get(), localInertia)
    , m_mass(mass)
    , m_motionState(std::move(motionState))
    , m_collisionShape(std::move(collisionShape))
    {
        // Bullet Physicsの中で剛体として扱わせる
        m_internalType = btCollisionObject::CO_RIGID_BODY;
    }
    
    CollisionObject(const btRigidBody::btRigidBodyConstructionInfo& info, std::unique_ptr<btMotionState> motionState = nullptr)
    : Super(info)
    , m_mass(info.m_mass)
    , m_motionState(std::move(motionState))
    {
        // Bullet Physicsの中で剛体として扱わせる
        m_internalType = btCollisionObject::CO_RIGID_BODY;
        if (!m_motionState)
        {
            setMotionStateWithMemoryManagement(std::unique_ptr<btMotionState>(new btDefaultMotionState()));
        }
    }
    
    btScalar getMass()const
    {
        return m_mass;
    }
    
    btCollisionShape*const getCollisionShapePtr()
    {
        return m_collisionShape.get();
    }
    
    void setCollisionShapeWithMemoryManagement(std::unique_ptr<btCollisionShape> collisionShape);
    
    void setMotionStateWithMemoryManagement(std::unique_ptr<btMotionState> motionState)
    {
        m_motionState = std::move(motionState);
    }
    
private:
    btScalar m_mass;
    
    // この2つの変数はメモリ管理のためのみに使用する→deleteを極力使用したくないため.
    // そこで、直接参照するgetter/setterは用意しないでおく
    std::unique_ptr<btMotionState> m_motionState;
    std::unique_ptr<btCollisionShape> m_collisionShape;
};

#endif /* collision_object_hpp */
