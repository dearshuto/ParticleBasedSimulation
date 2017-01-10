//
//  particle_algorithm.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

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

std::unique_ptr<fj::AdditionalProcedure> fj::Algorithm::generateProfileSystem(const fj::Algorithm::Profile profile)
{
    std::unique_ptr<fj::AdditionalProcedure> procedure;
    
    switch (profile) {
        case Profile::kSimulationTimeProfile:
            procedure.reset(new fj::SimulationTimeProfile);
            break;
        default:
            break;
    }
    
    return procedure;
}

void fj::Algorithm::addProfileSystem(std::unique_ptr<fj::AdditionalProcedure> additionalProcedure)
{
    // 新規追加された処理のプライオリティをもとに挿入箇所を探索
    const auto at = std::find_if(std::begin(m_additionalProcedures), std::end(m_additionalProcedures)
                                 , [&](std::unique_ptr<fj::AdditionalProcedure>& containedProfile){
                                     return additionalProcedure->getPriorityAdUInt() <= containedProfile->getPriorityAdUInt();
                                 });
    
    m_additionalProcedures.insert(at, std::move(additionalProcedure));
}
