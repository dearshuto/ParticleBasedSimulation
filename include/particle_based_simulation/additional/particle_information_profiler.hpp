//
//  particle_information_profiler.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef particle_information_profiler_hpp
#define particle_information_profiler_hpp

#include "additional_procedure.hpp"

namespace fj {
    class OverlapParticleWorld;
    class ParticleInformationProfiler;
}

/// ワールド内の fj::OverlapParticle の情報を解析するインタフェースを提供する.
/** 粒子の位置や速度などをプロファイルするには, このクラスの派生を作るといい. */
class fj::ParticleInformationProfiler : public fj::AdditionalProcedure
{
    typedef fj::AdditionalProcedure Super;
public:
    ParticleInformationProfiler() = delete;
    virtual~ParticleInformationProfiler() = default;
    
    ParticleInformationProfiler(const fj::OverlapParticleWorld& particleWorld, const Priority priority, const std::string& outputDirectory = "./")
    : Super(priority, outputDirectory)
    , m_world(particleWorld)
    {
        
    }
    
    const fj::OverlapParticleWorld& getParticleWorld()const
    {
        return m_world;
    }
    
private:
    const fj::OverlapParticleWorld& m_world;
};

#endif /* particle_information_profiler_hpp */
