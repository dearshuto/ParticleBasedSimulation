//
//  fine_particle_state.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#ifndef fine_particle_state_hpp
#define fine_particle_state_hpp

#include <memory>

namespace fj {
    class FineParticle;
    class FineParticleState;
}

class fj::FineParticleState
{
public:
    enum class State
    {
        kLock,
        kCollapse,
    };
protected:
    FineParticleState() = default;
public:
    virtual~FineParticleState() = default;
    
    static std::weak_ptr<fj::FineParticleState> GetInstance(const State state);
    
    /** 粉体粒子を好きにやっちゃって */
    virtual void execute(fj::FineParticle*const particle) = 0;
};

#endif /* fine_particle_state_hpp */
