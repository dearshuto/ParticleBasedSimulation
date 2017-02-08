//
//  particle_algorithm.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto on 2017/02/08.
//
//

#include <memory>
#include "particle_based_simulation/additional/povray/povray_output.hpp"
#include "particle_based_simulation/simulation/algorithm/general/particle_algorithm.hpp"

std::unique_ptr<fj::AdditionalProcedure> fj::ParticleAlgorithm::generateProfileSystem(const fj::ParticleAlgorithm::Profile profile)
{
    return std::unique_ptr<fj::POVRayOutput>{new fj::POVRayOutput{getOverlapParticleWorld()}};
}
