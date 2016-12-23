//
//  simulation_time_profile.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/25.
//
//

#include <fstream>
#include <ostream>
#include "particle_based_simulation/additional/profile/simulation_time_profile.hpp"

void fj::SimulationTimeProfile::startSimulationProfile(const fj::Algorithm& algorithm)
{
    // シミュレーションが始まる前に時間を取得しておく.
    m_start = std::chrono::system_clock::now();
}

void fj::SimulationTimeProfile::endSimulationProfile(const fj::Algorithm& algorithm)
{
    // シミュレーションが終わった時点での時間を取得する.
    auto currentStep = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now() - m_start ).count();

    updateSimulationTimeMinMax(currentStep);

    updateSimulationTimeAverage(currentStep);
    
    m_currentTime = currentStep;
}

void fj::SimulationTimeProfile::updateSimulationTimeMinMax(const MilliSecTime &currentStep)
{
    // 前フレームまでの最大値と最小値を今回のフレームと比較して, 必要があれば更新する.
    
    if (currentStep > m_max)
    {
        m_max = currentStep;
    }
    
    if (currentStep < m_min)
    {
        m_min = currentStep;
    }
}

void fj::SimulationTimeProfile::updateSimulationTimeAverage(const MilliSecTime &currentStep)
{
    m_average = (m_average == 0) ? currentStep : (currentStep + m_average) / 2.0;
}

void fj::SimulationTimeProfile::terminate()
{
    if (m_isOutputLogWhenTerminate)
    {
        std::ofstream output(getOutputDirectory() + "/simulation_time.log");
        output << getFormattedTimeData();
    }
}

std::string fj::SimulationTimeProfile::getDataAsString()const
{
    return getFormattedTimeData();
}

std::string fj::SimulationTimeProfile::getFormattedTimeData()const
{
    std::string output = "";
    
    output += "Max: " + std::to_string(m_max / 1000.0) + " sec\n";
    output += "Min: " + std::to_string(m_min / 1000.0) + " sec\n";
    output += "Avg: " + std::to_string( m_average / 1000.0) + " sec\n";
    
    return output;
}
