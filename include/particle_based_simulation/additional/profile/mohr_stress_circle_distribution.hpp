//
//  mohr_stress_circle_distribution.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/28.
//
//

#ifndef mohr_stress_circle_distribution_hpp
#define mohr_stress_circle_distribution_hpp

#include "particle_based_simulation/additional/rheorogy_simulator_profiler.hpp"

namespace fj {
    class MohrStressCircleDistribution;
}

/// モールの応力円の半径の分布をプロファイリングする
/** 各粒子にひも付いたモールの応力円の半径を調べて, ある大きさのモールの応力円の数をカウントする.
 * gnuplotのコマンドとして書き出す昨日も提供する. 
 * プロファイリングとして作ってみたものの, あんまり面白い結果は得られなかった. */
class fj::MohrStressCircleDistribution : public fj::RheorogySimulatorProfiler
{
    typedef fj::RheorogySimulatorProfiler Super;
public:
    MohrStressCircleDistribution() = delete;
    ~MohrStressCircleDistribution() = default;

    MohrStressCircleDistribution(const fj::RheorogyAlgorithm& rheorogyAlgorithm)
    : Super(rheorogyAlgorithm, Priority::kI_dont_care)
    {
        
    }

    void startSimulationProfile(const fj::Algorithm& algorithm)override;
    
    void endSimulationProfile(const fj::Algorithm& algorithm)override;
    
    void terminate()override;
    
    /** @copydoc Super::getDataAsString() */
    std::string getDataAsString()const override;
    
    void setGraph(const float min, const float max, const float duration);
    
private:
    float m_min;
    float m_max;
    float m_duration;
};

#endif /* mohr_stress_circle_distribution_hpp */
