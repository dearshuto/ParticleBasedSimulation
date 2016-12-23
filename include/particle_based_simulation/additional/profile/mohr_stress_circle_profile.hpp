//
//  mohr_stress_circle_profile.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/27.
//
//

#ifndef mohr_stress_circle_profile_hpp
#define mohr_stress_circle_profile_hpp

#include <functional>
#include "particle_based_simulation/additional/rheorogy_simulator_profiler.hpp"

namespace fj {
    class MohrStressCircleProfile;
}

/// n番目に生成された粒子の崩壊曲線を可視化する. gnuplotで描画できる形式で書き出す.
/** 本来なら複数の粒子を追跡できるようにしたいが, とりあえず1つの粒子だけを追跡する. */
class fj::MohrStressCircleProfile : public fj::RheorogySimulatorProfiler
{
    typedef fj::RheorogySimulatorProfiler Super;
public:
    MohrStressCircleProfile() = delete;
    ~MohrStressCircleProfile() = default;

    MohrStressCircleProfile(const fj::RheorogyAlgorithm& rheorogyAlgorithm)
    : Super(rheorogyAlgorithm, Priority::kI_dont_care)
    {
        
    }
    
    void startSimulationProfile(const fj::Algorithm& algorithm)override;
    
    void endSimulationProfile(const fj::Algorithm& algorithm)override;
    
    void terminate()override;
    
    /** @copydoc Super::getDataAsString() */
    std::string getDataAsString()const override;
    
    void setFilter(const std::function<bool(const int index)>& function)
    {
        m_filterFunction = function;
    }
    
private:
    std::function<bool(const int index)> m_filterFunction;
};

#endif /* mohr_stress_circle_profile_hpp */
