//
//  overlap_particle_world.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef particle_world_hpp
#define particle_world_hpp

#include <memory>
#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "particle_based_simulation/simulation/bullet_algorithm/fine_particle_simulation_collision_configuration.hpp"
#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

namespace fj {
    class OverlapParticle;
    class OverlapParticleWorld;
}

/// Bullet Physics のフレームワークをラップしたクラス.
/** 登録した剛体に対して, 「衝突判定および検出」, 「アクセスするインタフェースの提供」, 「位置更新」の3つを担う.
 * 「粒子ー剛体」の衝突は, 粒子を剛体の球としてこのクラス内で力学計算をするが, 「粒子ー粒子」の衝突は検出はするが実際の力学計算は行わない.
 * 実際の粒子シミュレーションは fj::Algorithm を継承したクラスに任せてある.
 * 上記の内容を実現するにはアルゴリズムを分岐する必要があるが, これは fj::FineParticleSimulationCollisionConfiguration が担っている. */
class fj::OverlapParticleWorld
{
public:
    enum class Dimension : uint8_t
    {
        ThreeD,
        
        /// x-y平面の移動のみのシミュレーションを実行する
        TwoD,
    };
public:
    /// ワールド内の粒子を走査するイテレータ
    class Iterator
    {
    public:
        Iterator() = default;
        virtual~Iterator() = default;
        virtual bool hasNext() = 0;
        virtual const fj::OverlapParticle& next() = 0;
    };
    
public:
    OverlapParticleWorld()
    : m_collisionConfiguration( new fj::FineParticleSimulationCollisionConfiguration() )
    , m_dispatcher( new btCollisionDispatcher( m_collisionConfiguration.get() ) )
    , m_pairCache( new btDbvtBroadphase() )
    , m_constraintSolver( new btSequentialImpulseConstraintSolver() )
    , m_world( new btDiscreteDynamicsWorld( m_dispatcher.get()
                                           , m_pairCache.get()
                                           , m_constraintSolver.get()
                                           , m_collisionConfiguration.get())
              )
    
    {
        // btGhostObjectがオーバラップしたオブジェクトを検知できるようにコールバックを登録しておく
       // m_world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    }
    
    virtual~OverlapParticleWorld() = default;
    
    /** ワールド内の粒子を走査するイテレータを作成する. */
    virtual std::unique_ptr<Iterator> iterator()const = 0;
    
    /** ワールド内の物体の位置を更新する. */
    void updateAllObjectsPosition(const btScalar timestep);

    
    /** シミュレーション対象を追加する.
     * この関数を使って登録した剛体は、プログラム側で解放されます
     * @param body Particle以外の剛体 */
    void addRigidBody(std::unique_ptr<fj::CollisionObject> body);
    
	void addRigidBody(std::unique_ptr<btRigidBody> btBody);

    void switchSimulatorDimension(const Dimension dimension);
    
    void setGravity(const btVector3& gravity)
    {
        m_world->setGravity(gravity);
    }
    
    btBroadphasePairArray*const getOverlappingPairArrayPtr()
    {
        return &m_pairCache->getOverlappingPairCache()->getOverlappingPairArray();
    }
    
protected:
    btDynamicsWorld* getWorldPtr()
    {
        return m_world.get();
    }
    
private:
    Dimension m_dimension;
    
    //---------------- Bullet Physicsのフレームワークを利用するためのインスタンス ----------------------//
    /** Bullet Physicsは生ポインタで全ての処理をするので, メモリの管理はユーザ側でしなくてはならない
     * Bullet Physicsの中でシミュレーション対象となる剛体のメモリ管理用のコンテナ */
    std::vector<std::unique_ptr<fj::CollisionObject>> m_rigidBody;
    
	// btRigidBodyを生で保持する用
	std::vector<std::unique_ptr<btRigidBody>> m_btRigidBody;

    // Bullet Physicsを利用するために最低限必要なインスタンス
    std::unique_ptr<btCollisionConfiguration> m_collisionConfiguration;
    std::unique_ptr<btDispatcher> m_dispatcher;
    std::unique_ptr<btBroadphaseInterface> m_pairCache;
    std::unique_ptr<btConstraintSolver> m_constraintSolver;
    std::unique_ptr<btDiscreteDynamicsWorld> m_world;
};

#endif /* particle_world_hpp */
