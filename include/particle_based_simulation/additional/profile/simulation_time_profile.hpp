//
//  simulation_time_profile.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/25.
//
//

#ifndef simulation_time_profile_hpp
#define simulation_time_profile_hpp

#include <chrono>
#include <limits>
#include <string>
#include "particle_based_simulation/additional/additional_procedure.hpp"

namespace fj {
    class SimulationTimeProfile;
}

/// 1フレームのシミュレーション時間を計測する.
/**  */
class fj::SimulationTimeProfile : public fj::AdditionalProcedure
{
    typedef fj::AdditionalProcedure Super;
    typedef std::chrono::system_clock::time_point time_point;
    typedef long long MilliSecTime;
public:
    SimulationTimeProfile(const bool isOutputLogWhenTermitate = false)
    : Super(Priority::kAbsolutelyLast)
    , m_average(0)
    , m_max(0)
    , m_min(std::numeric_limits<MilliSecTime>::infinity())
    , m_isOutputLogWhenTerminate(isOutputLogWhenTermitate)
    {
        
    }

    virtual~SimulationTimeProfile() = default;

    virtual void startSimulationProfile(const fj::Algorithm& algorithm)override;
    
    virtual void endSimulationProfile(const fj::Algorithm& algorithm)override;
    
    virtual void terminate()override;
    
    std::string getDataAsString()const override;
protected:
    
    void updateSimulationTimeMinMax(const MilliSecTime& currentStep);
    
    void updateSimulationTimeAverage(const MilliSecTime& currentStep);
    
    std::string getFormattedTimeData()const;
public:
    
    const time_point& getStartTime()const
    {
        return m_start;
    }
    
    const MilliSecTime& getCurrentTime()const
    {
        return m_currentTime;
    }
    
    const MilliSecTime& getCurrentAverage()const
    {
        return m_average;
    }
    
    const MilliSecTime& getMax()const
    {
        return m_max;
    }
    
    const MilliSecTime& getMin()const
    {
        return m_min;
    }
    
private:
    time_point m_start;
    
    MilliSecTime m_currentTime;
    
    MilliSecTime m_average;
    
    MilliSecTime m_max;
    
    MilliSecTime m_min;
    
    const bool m_isOutputLogWhenTerminate;
};

#endif /* simulation_time_profile_hpp */
