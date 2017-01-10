//
//  particle_algorithm.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef particle_algorithm_hpp
#define particle_algorithm_hpp

#include <memory>
#include <vector>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "particle_based_simulation/additional/povray/povray_output.hpp"
#include "particle_based_simulation/simulation/general_particle_world.hpp"
#include "particle_based_simulation/simulation/algorithm/general/algorithm.hpp"

namespace fj {
    template<class Parameter> class Particle;
    template<class T> class GeneralParticleWorld;
    template<class Parameter> class ParticleAlgorithm;
}
class btVector3;

/// あるパラメータをもとに計算する粒子法アルゴリズム
/** シミュレーションに必要な任意のパラメータを指定してシミュレーションができる.
 * 一般化するためにテンプレートテクニックを使ったので, ヘッダしか存在しない.
 * @param Parameter このアルゴリズムを実行するのに必要で, fj::Particle にないパラメータ. */
template<class Parameter>
class fj::ParticleAlgorithm : public fj::Algorithm
{
protected:
    /// シミュレーションに必要なパラメータを保持した粒子.
    typedef fj::Particle<Parameter> Particle;
    
    // このアルゴリズムに対応したワールド.
    typedef fj::GeneralParticleWorld<Particle> ParticleWorld;
    
    // ワールドが提供する構造体名長いので別名をつけておく
    typedef typename ParticleWorld::ParticlesContactInfo ParticlesContactInfo;
public:
    /// fj::ParticleAlgorithm の情報をプロファイルするシステム一覧
    enum class Profile : uint8_t
    {
        kPOVRayOutput,
    };
public:
    ParticleAlgorithm()
    {
        
    }
    virtual~ParticleAlgorithm() = default;
    
    /** 追加処理を作成する. */
    std::unique_ptr<fj::AdditionalProcedure> generateProfileSystem(const Profile profile)
    {
        std::unique_ptr<fj::AdditionalProcedure> procedure;
        switch (profile) {
            case Profile::kPOVRayOutput:
                procedure.reset(new fj::POVRayOutput(getWorld()));
                break;
            default:
                break;
        }
        return procedure;
    }


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

#endif /* algorithm_hpp */
