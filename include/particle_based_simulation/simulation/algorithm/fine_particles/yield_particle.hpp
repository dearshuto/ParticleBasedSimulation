//
//  yield_particle.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#ifndef yield_particle_hpp
#define yield_particle_hpp

#include <tuple>
#include "particle_based_simulation/simulation/algorithm/fine_particles/fine_particle_state.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/warren_spring_curve.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/mohr_stress_circle.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/normal_force_container.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle.hpp"

namespace fj {
    struct RheorogyParameter;
    class YieldParticle;
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

class fj::YieldParticle : public fj::DiscritizedParticle<fj::RheorogyParameter>
{
    typedef fj::DiscritizedParticle<fj::RheorogyParameter> Super;
public:
    YieldParticle(const btScalar overlap, const float mass, std::unique_ptr<fj::NormalForceContainer> normal, const btScalar rigidRadius)
    : Super(overlap, mass, normal->getNormalContainerSharedPtr())
    , m_normalForceContainer(std::move(normal))
    {
        
    }
    
    void addForce(const btVector3& force);
    
    void clearForce();
    
    bool hasContactForce()const;
    
    /// first->max, second->min
    std::pair<btScalar, btScalar> getMinMax()const;
private:
    std::unique_ptr<fj::NormalForceContainer> m_normalForceContainer;
};

#endif /* yield_particle_hpp */
