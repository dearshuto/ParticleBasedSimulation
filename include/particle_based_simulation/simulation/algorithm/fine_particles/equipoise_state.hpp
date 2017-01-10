//
//  equipoise_state.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/10.
//
//

#ifndef equipoise_state_hpp
#define equipoise_state_hpp

#include "collapse_state.hpp"

namespace fj {
    class EquipoiseState;
}

/// 粉体粒子が均衡状態であることを示す
class fj::EquipoiseState : public fj::FineParticleState
{
public:
    EquipoiseState() = default;
    ~EquipoiseState() = default;
    
    void update(fj::Particle<fj::RheorogyParameter>* particle)override;
};

#endif /* equipoise_state_hpp */
