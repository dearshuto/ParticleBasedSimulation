//
//  collapse_state.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#ifndef collapse_state_hpp
#define collapse_state_hpp

#include "fine_particle_state.hpp"

namespace fj {
    class CollapseState;
}

class fj::CollapseState : public fj::FineParticleState
{
public:
    CollapseState() = default;
    virtual~CollapseState() = default;
    
    void execute(fj::FineParticle*const particle) override;
};

#endif /* collapse_state_hpp */