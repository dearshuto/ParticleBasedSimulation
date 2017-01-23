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

/// Bullet Physics のフレームワークの中でシミュレーション可能な物体のラッパ.
/** Bullet Physics はGPU実装を考慮したメモリ配置がされるので, 独自に拡張するとメモリ割当がうまくいかないことがあった.
 * そこで, 継承ではなく, ラッパを採用する.
 * シミュレーションしたいオブジェクトは, すべてこのクラスの派生であるべき. */
class fj::CollisionObject
{
protected:
    CollisionObject() = delete;

    /**
     * @param mass 質量[kg]
     * @param motionState Bullet Physicsが提供するオブジェクトの位置情報を管理するクラス. このコンストラクタがを呼ぶ段階でnullptrであっても問題ない. ただしインスタンス化したあとで値をセットしないとぬるぽで落ちる
     * @param collisionShape Bullet Physicsの衝突判定で使用される形状. このコンストラクタを呼ぶ段階でnullptrであっても問題ない. ただしインスタンス化したあとで値をセットしないとぬるぽエラーで落ちる
     * @param localInertia 各軸まわりにおける回転のしやすさ. ゼロベクトルの場合, 回転運動が起きなくなる. デフォルトでは回転しないように設定してある*/
    CollisionObject(const btScalar mass, std::unique_ptr<btCollisionShape> collisionShape);

public:
    virtual~CollisionObject() = default;
    
    void applyCentralForce(const btVector3& force);
    
    const btVector3& getLinearVelocity()const;
    
    void setLinearVelocity(const btVector3& velocity);
    
    btScalar getMass()const
    {
        return m_mass;
    }
    
    std::unique_ptr<btCollisionShape>& getCollisionShapePtr()
    {
        return m_collisionShape;
    }
    
    const btRigidBody& getRigidBody()const
    {
        return *m_rigidBody;
    }
    
    const btVector3& getPosition()const;
    
    void setPosition(const btVector3& position);

    std::unique_ptr<btRigidBody>& getRigidBodyPtr()
    {
        return m_rigidBody;
    }

protected:
    const btCollisionShape& getCollisionShape()const
    {
        return *m_collisionShape;
    }
    
    void setCollisionShape(std::unique_ptr<btCollisionShape> collisionShape)
    {
        m_collisionShape = std::move(collisionShape);
    }
    
private:
    /** コンストラクタの中で行われるインスタンスのセットアップ. */
    void init(const btScalar mass, std::unique_ptr<btCollisionShape> collisionShape);
private:
    
    btScalar m_mass;
    
    // この2つの変数はメモリ管理のためのみに使用する→deleteを極力使用したくないため.
    // そこで、直接参照するgetter/setterは用意しないでおく
    std::unique_ptr<btMotionState> m_motionState;
    std::unique_ptr<btCollisionShape> m_collisionShape;
    std::unique_ptr<btRigidBody> m_rigidBody;
};

#endif /* collision_object_hpp */
