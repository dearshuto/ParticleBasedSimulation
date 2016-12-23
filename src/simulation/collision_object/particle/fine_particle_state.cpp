//
//  fine_particle_state.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/12.
//
//

#include "particle_based_simulation/simulation/collision_object/particle/collapse_state.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/fine_particle_state.hpp"

std::weak_ptr<fj::FineParticleState> fj::FineParticleState::GetInstance(const fj::FineParticleState::State state)
{
    static std::shared_ptr<fj::CollapseState> collapseState{new fj::CollapseState{}};
    
    switch (state) {
        case fj::FineParticleState::State::kLock:
            return std::weak_ptr<fj::CollapseState>{};
            break;
        case fj::FineParticleState::State::kCollapse:
            return std::weak_ptr<fj::CollapseState>{collapseState};
            break;
        default:
            break;
    }
    
    return std::weak_ptr<fj::CollapseState>{};
}
