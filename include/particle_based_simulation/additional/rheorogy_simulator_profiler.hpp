//
//  fine_particle_simulator_profiler.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef rheorogy_simulator_profiler_hpp
#define rheorogy_simulator_profiler_hpp

#include "particle_based_simulation/additional/additional_procedure.hpp"

namespace fj {
    class RheorogyAlgorithm;
    class RheorogySimulatorProfiler;
}

/// fj::RheorogyAlgorithm をプロファイルするインタフェースを提供する.
/** レオロジーモデルを利用したシミュレーションを解析したいときにはこちらのクラスを派生するといい. */
class fj::RheorogySimulatorProfiler : public fj::AdditionalProcedure
{
    typedef fj::AdditionalProcedure Super;
public:
    RheorogySimulatorProfiler() = delete;
    virtual~RheorogySimulatorProfiler() = default;
    
    RheorogySimulatorProfiler(const fj::RheorogyAlgorithm& rheorogyAlgorithm, const Priority priority, const std::string& outputDirectory = "./")
    : Super(priority, outputDirectory)
    , m_rheorogyAlgorithm(rheorogyAlgorithm)
    {
        
    }
    
    const fj::RheorogyAlgorithm& getRheorogyAlgorithm()const
    {
        return m_rheorogyAlgorithm;
    }
private:
    const fj::RheorogyAlgorithm& m_rheorogyAlgorithm;
};

#endif /* fine_particle_simulator_profiler_hpp */
