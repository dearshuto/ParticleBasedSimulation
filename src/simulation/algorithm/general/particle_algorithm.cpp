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

std::weak_ptr<fj::POVRayOutput> fj::ParticleAlgorithm::setupPOVRaySceneOutputSystem()
{
    std::unique_ptr<fj::POVRayOutput> povray{new fj::POVRayOutput(getOverlapParticleWorld())};
    std::weak_ptr<fj::AdditionalProcedure> result = addProfileSystem(std::move(povray));
    auto returnPtr = std::static_pointer_cast<fj::POVRayOutput>(result.lock());
    return std::weak_ptr<fj::POVRayOutput>{returnPtr};
}
