//
//  fine_particle_state.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/10.
//
//

#ifndef fine_particle_state_hpp
#define fine_particle_state_hpp

namespace fj {
    class YieldParticle;
    class FineParticleState;
}

/// 粉体の状態
class fj::FineParticleState
{
protected:
    FineParticleState() = default;
public:
    virtual~FineParticleState () = default;
    
    /** 粉体粒子になにかしらの影響を与える
     * @pre 粉体粒子にかかる力が計算済み*/
    virtual void update(fj::YieldParticle* yieldParticle) = 0;
};

#endif /* fine_particle_state_hpp */
