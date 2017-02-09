//
//  particle_algorithm.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#include <algorithm>
#include "particle_based_simulation/additional/profile/simulation_time_profile.hpp"
#include "particle_based_simulation/simulation/algorithm/general/particle_algorithm.hpp"

void fj::Algorithm::startProfiling()
{
    for (auto& profile: *getAdditionalProceduresPtr())
    {
        profile->startSimulationProfile(*this);
    }
}

void fj::Algorithm::stepSimulation(const float timestep)
{
    ++m_simulationStep;
    startProfiling();
    execute(timestep);
    endProfiling();
}

void fj::Algorithm::endProfiling()
{
    for (auto reverseIterator = getAdditionalProceduresPtr()->crbegin(); reverseIterator != getAdditionalProceduresPtr()->crend(); ++reverseIterator)
    {
        (*reverseIterator)->endSimulationProfile(*this);
    }
}

void fj::Algorithm::terminate()
{
    // とりあえずプロファイリングを終わらせればOK
    for (auto& profile : *getAdditionalProceduresPtr())
    {
        profile->terminate();
    }
}

std::weak_ptr<fj::SimulationTimeProfile> fj::Algorithm::setupSimulationTimeProfileSystem()
{
    std::unique_ptr<fj::SimulationTimeProfile> profiler{new fj::SimulationTimeProfile};
    std::weak_ptr<fj::AdditionalProcedure> result = addProfileSystem(std::move(profiler));
    std::shared_ptr<fj::SimulationTimeProfile> casted = std::static_pointer_cast<fj::SimulationTimeProfile>(result.lock());
    return std::weak_ptr<fj::SimulationTimeProfile>{casted};
}

std::weak_ptr<fj::AdditionalProcedure> fj::Algorithm::addProfileSystem(std::unique_ptr<fj::AdditionalProcedure> additionalProcedure)
{
    // 新規追加された処理のプライオリティをもとに挿入箇所を探索
    const auto at = std::find_if(std::begin(m_additionalProcedures), std::end(m_additionalProcedures)
                                 , [&](std::shared_ptr<fj::AdditionalProcedure>& containedProfile){
                                     return additionalProcedure->getPriorityAdUInt() <= containedProfile->getPriorityAdUInt();
                                 });

    std::shared_ptr<fj::AdditionalProcedure> instance{std::move(additionalProcedure)};
    m_additionalProcedures.insert(at, instance);
    return std::weak_ptr<fj::AdditionalProcedure>(instance);
}
