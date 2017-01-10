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

/// 粉体粒子が崩壊状態であることを示す
class fj::CollapseState : public fj::FineParticleState
{
public:
    CollapseState() = default;
    virtual~CollapseState() = default;
    
    void update(fj::Particle<fj::RheorogyParameter>* particle)override;
};

#endif /* collapse_state_hpp */
