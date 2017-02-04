//
//  general_particle_world.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#ifndef overlap_particle_world_hpp
#define overlap_particle_world_hpp

#include <memory>
#include <vector>
#include "overlap_particle_world.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"


namespace fj {
    template<class Particle>class GeneralParticleWorld;
}

/// 一般的な粒子を管理するワールド.
/** 理論上, どんな粒子のシミュレーションもこのクラスで管理できる（はず）.
 * fj::ParticleAlgorithm のメンバ変数として提供されています. 
 * このクラスをプログラマがインスタンス化して使うことは想定していません. インスタンス化して嬉しい局面は思いつきませんね.
 * fj::OverlapParticle を継承したクラス以外がテンプレート引数に渡されると, イテレータが作成できないのでコンパイルエラーが起きる. 
 * このクラスが記述されているファイルはとても大きいものですが, その大半が内部クラスによるものなのでご安心を. */
template <class Particle>
class fj::GeneralParticleWorld : public fj::OverlapParticleWorld
{
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------
    //---- 内部クラス --------------------------------------------------------------------------------------------------------------------------------------------
public:
    /// 粉体粒子間の情報を計算すると同時に保持するための構造体.
    /** 相対ベクトルと粒子間距離はどうせ使うので計算して内部に保持させておく. */
    struct ParticlesContactInfo
    {
        ParticlesContactInfo(Particle*const particle1, Particle*const particle2)
        : Particle1(particle1)
        , Particle2(particle2)
        , kDirection12(particle2->getPosition() - particle1->getPosition())
        , kDistance(kDirection12.norm())
        , kNormalizedDirection12(kDirection12 / kDistance)
        , kOverlap((particle1->getOverlapRange() + particle2->getOverlapRange()) - kDistance)
        {
            
        }
        
        Particle*const Particle1;
        Particle*const Particle2;
        const btVector3 kDirection12;
        const btScalar kDistance;
        const btVector3 kNormalizedDirection12;
        const float kOverlap;
    };
private:
    
    /// ワールド内の粒子を走査するイテレータ.
    /** STLのイテレータを利用した走査をラッパしたクラス.
     * 内部の粒子情報にアクセスするためのイテレータなので, このクラスを介して取得した粒子の情報を変更することはできない. */
    class Iterator : public fj::OverlapParticleWorld::Iterator
    {
        typedef fj::GeneralParticleWorld<Particle> Parent;
    public:
        Iterator() = delete;
        virtual~Iterator() = default;
        
        Iterator(const Parent* parent)
        : m_now( std::begin(parent->m_particles) )
        , m_end( std::end(parent->m_particles) )
        {
            
        }
        bool hasNext()override{ return m_now != m_end; } //冗長なので1行にしました
        const fj::OverlapParticle& next()override
        {
            const fj::OverlapParticle& particle = **m_now;
            ++m_now; //これ忘れたら無限ループに陥る
            return particle;
        }
    private:
        typename std::vector<std::unique_ptr<Particle>>::const_iterator m_now;
        const typename std::vector<std::unique_ptr<Particle>>::const_iterator m_end;
    };
    
    /// 近傍に入った粒子のペアを走査するイテレータ.
    /** Bullet Physics のフレームワークから衝突ペアを抽出する工程をラッパしたものです. */
    class OverlapParticlePairIterator
    {
        typedef fj::GeneralParticleWorld<Particle> Parent;
    public:
        OverlapParticlePairIterator() = delete;
        ~OverlapParticlePairIterator() = default;
        
        OverlapParticlePairIterator(Parent* parent)
        : m_index(0)
        , m_pairArray(parent->getOverlappingPairArrayPtr())
        {
            
        }
        
        bool hasNext()
        {
            using ParticleBase = fj::Particle<typename Particle::ParameterType>;
            while(m_index < m_pairArray->size())
            {
                // Bullet Physics のフレームワークから, 衝突が起きそうなペアを抽出する.
                const auto pair = m_pairArray->at(m_index);
                btCollisionObject* body0 = static_cast<btCollisionObject*>(pair.m_pProxy0->m_clientObject);
                btCollisionObject* body1 = static_cast<btCollisionObject*>(pair.m_pProxy1->m_clientObject);
                
                // 粒子か判定するために, まずは fj::Particle かどうかを判定する
                ParticleBase*const particle1 = ParticleBase::Upcast(body0);
                ParticleBase*const particle2 = ParticleBase::Upcast(body1);
                
                // 粒子同士の衝突だったら, オーバーラップが発生しているか判定する
                if (particle1 && particle2)
                {
                    // ここで, 実際の型に変換する.
                    m_contactInfo = new ParticlesContactInfo{static_cast<Particle*const>(particle1), static_cast<Particle*const>(particle2)};
                    if ( m_contactInfo->kOverlap > 0 )
                    {
                        return true;
                    }
                    else
                    {// オーバラップしてなかったらインデクスを増やしてもう一周.
                        m_index++;
                        continue;
                    }
                }
                else
                {// 違ったらインデックスを増やしてもう一周.
                    m_index++;
                    continue;
                }
            }
            
            // 最後まで見つからなかったらfalse
            return false;
        }
        //
        ParticlesContactInfo next()
        {
            m_index++; //次を指すようにしておかないと無限ループに陥る
            return *m_contactInfo;
        }
    private:
        /// 操作中のインデックス
        unsigned int m_index;
        ParticlesContactInfo* m_contactInfo;
        btBroadphasePairArray* m_pairArray;
    };

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------
    //---- クラス本体 --------------------------------------------------------------------------------------------------------------------------------------------
public:
    GeneralParticleWorld() = default;
    virtual~GeneralParticleWorld() = default;
    
    /** @copydetail fj::OverlapParticleWorld::iterator */
    std::unique_ptr<fj::OverlapParticleWorld::Iterator> iterator()const override
    {
        return std::unique_ptr<fj::OverlapParticleWorld::Iterator>(new Iterator{this});
    }
    
    /** ワールド内でオーバーラップした粒子ペアを走査するイテレータを取得する. */
    std::unique_ptr<OverlapParticlePairIterator> overlapParticlePairIterator()
    {
        return std::unique_ptr<OverlapParticlePairIterator>(new OverlapParticlePairIterator{this});
    }
    
    /** パーティクルを追加する.  */
    void addParticle(std::unique_ptr<Particle> particle)
    {
        getWorldPtr()->addRigidBody(particle->getRigidBodyPtr().get());
        m_particles.push_back(std::move(particle));
    }
    
    /** 指定された粒子を削除する
     * @param particle 削除対象. particleがnullptrの場合の挙動は未定義.
     * @pre particleはワールド内に存在するインスタンスである. */
    void removeParticle(Particle*const particle)
    {
        // Bullet Physicsからの削除
        getWorldPtr()->removeCollisionObject(particle);
        
        // m_particlesの中に同一のアドレスをもつインスタンスが存在しないことを前提とする
        auto inContainer = std::find_if(m_particles.begin(), m_particles.end()
                                        , [particle](std::unique_ptr<Particle>& containerComponent){
                                            return containerComponent.get() == particle;
                                        });
        assert(inContainer != m_particles.end());
        m_particles.erase(inContainer);
    }
    
public:
    const std::vector<std::unique_ptr<Particle>>& getParticles()const
    {
        return m_particles;
    }

private:
    std::vector<std::unique_ptr<Particle>> m_particles;
};

#endif /* particle_world_hpp */
