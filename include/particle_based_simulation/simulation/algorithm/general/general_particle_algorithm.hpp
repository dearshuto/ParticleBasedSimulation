//
//  general_particle_algorithm.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto on 2017/02/08.
//
//

#ifndef general_particle_algorithm_hpp
#define general_particle_algorithm_hpp

#include <memory>
#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "particle_based_simulation/additional/povray/povray_output.hpp"
#include "particle_based_simulation/simulation/general_particle_world.hpp"
#include "particle_based_simulation/simulation/algorithm/general/algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"
#include "particle_algorithm.hpp"

namespace fj {
    template<class T> class GeneralParticleWorld;
    template<class Particle> class GeneralParticleAlgorithm;
}
class btVector3;

/// あるパラメータをもとに計算する粒子法アルゴリズム
/** シミュレーションに必要な任意のパラメータを指定してシミュレーションができる.
 * 一般化するためにテンプレートテクニックを使ったので, ヘッダしか存在しない.
 * @param Parameter このアルゴリズムを実行するのに必要で, fj::Particle にないパラメータ. */
template<class Particle>
class fj::GeneralParticleAlgorithm : public fj::ParticleAlgorithm
{
protected:
    // このアルゴリズムに対応したワールド.
    typedef fj::GeneralParticleWorld<Particle> ParticleWorld;
    
    // ワールドが提供する構造体名長いので別名をつけておく
    typedef typename ParticleWorld::ParticlesContactInfo ParticlesContactInfo;

public:
    GeneralParticleAlgorithm()
    {
        
    }
    virtual~GeneralParticleAlgorithm() = default;
    
private:
    /** シミュレーションを進める. */
    void execute(const float timestep)override
    {
        // 粒子にかかる力を計算して粒子に蓄積させる
        accumulateParticleForce();
        
        // 粒子にかかる力をもとに何かしらの処理を追加する.
        analyze();
        
        // ↑ここで計算した力をもとに↓ここで位置更新する.
        getWorldPtr()->updateAllObjectsPosition(timestep);
    }
    
    /** 粒子間力を計算して粒子に蓄積させていく */
    virtual void accumulateParticleForce() = 0;
    
    /** 粒子に集約した力をもとに何かしらの処理を追加したいときはこの関数をオーバーライドする
     * @pre すべての粒子に力が集約されている. */
    virtual void analyze(){} // デフォルトは何もしない.
    
public:
    
    const fj::OverlapParticleWorld& getOverlapParticleWorld()const override
    {
        return getWorld();
    }
    
    fj::OverlapParticleWorld* getOverlapParticleWorldPtr()override
    {
        return getWorldPtr();
    }
    
    ParticleWorld* getWorldPtr()
    {
        return &m_world;
    }
    
    const ParticleWorld& getWorld()const
    {
        return m_world;
    }
private:
    
    /// このアルゴリズムに紐付いたワールド
    ParticleWorld m_world;
};

#endif /* general_particle_algorithm_hpp */
