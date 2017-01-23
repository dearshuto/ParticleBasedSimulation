//
//  rheorogy_algorithm.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#ifndef rheorogy_algorithm_hpp
#define rheorogy_algorithm_hpp

#include <memory>
#include "particle_based_simulation/simulation/algorithm/fine_particles/fine_particle_state.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/warren_spring_curve.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/mohr_stress_circle.hpp"
#include "particle_based_simulation/simulation/algorithm/general/particle_algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"

namespace fj {
    struct RheorogyParameter;
    class RheorogyAlgorithm;
}

struct fj::RheorogyParameter
{
    /** 剛体としての半径 */
    btScalar Radius;
    
    /** レオロジーモデルで使用するのばね定数 */
    btScalar SpringParameter;
    
    /** レオロジーモデルで使用するダッシュポッドのブースト値 */
    btScalar DashpodEnvelope;
    
    /** Stateパターンで崩壊を表現しようとしているところ */
    std::unique_ptr<fj::FineParticleState> State;
    
    /** 粉体崩壊曲線を定義するのに必要なパラメータ */
    fj::WarrenSpringCurve WarrenSpringCurve;
    
    /** モールの応力円. fj::FineParticleState の内部に持たせようかと思ってる */
    fj::MohrStressCircle MohrStressCircle;
};

/// レオロジーモデルを利用して粒子間力を計算するアルゴリズム.
/**  */
class fj::RheorogyAlgorithm : public fj::ParticleAlgorithm<fj::RheorogyParameter>
{
    typedef fj::ParticleAlgorithm<fj::RheorogyParameter> Super;
public:
    RheorogyAlgorithm() = default;
    ~RheorogyAlgorithm() = default;
    
    /** ファクトリー関数
     * @todo 生成する粒子のオーバーラップの範囲と質量を指定できるといいな. */
    static std::unique_ptr<Particle> GenerateParticle(const btVector3& position)
    {
        auto particle = Particle::GenerateParticle(0.5/*overlap*/, 0.5/*mass*/, position);
        particle->getParameterPtr()->Radius = particle->getOverlapRange() * 0.5;
        return particle;
    }
    
private:
    void accumulateParticleForce()override;
    
    void analyze()override;
    
    void updateParticleState();
    
    void applyNormalComponentContactForce(const ParticlesContactInfo& contactInfo);
    
    void applyTangentialComponentContactForce(const ParticlesContactInfo& contactInfo);
    
    void applyCollisionParticleForce();
    
    btScalar computeDashpodEnvelope(const Particle &particle1, const Particle &particle2)const;
    
    btScalar computeReducedMass(const Particle &particle1, const Particle &particle2)const;
    
    void applyVandeerWaalsForce(const ParticlesContactInfo& contactInfo)const;
};

#endif /* rheorogy_algorithm_hpp */
