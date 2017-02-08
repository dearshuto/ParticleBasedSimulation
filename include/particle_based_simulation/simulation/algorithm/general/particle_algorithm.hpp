//
//  particle_algorithm.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef particle_algorithm_hpp
#define particle_algorithm_hpp

#include "algorithm.hpp"

namespace fj {
    class OverlapParticleWorld;
    class ParticleAlgorithm;
}

/// 粒子のオーバーラップを検出するワールドへのインタフェース
class fj::ParticleAlgorithm : public fj::Algorithm
{
public:
    /// fj::ParticleAlgorithm の情報をプロファイルするシステム一覧
    enum class Profile : uint8_t
    {
        kPOVRayOutput,
    };
public:
    ParticleAlgorithm() = default;
    virtual~ParticleAlgorithm() = default;
    
    /** 追加処理を作成する. */
    std::unique_ptr<fj::AdditionalProcedure> generateProfileSystem(const Profile profile);
    
    
    virtual const fj::OverlapParticleWorld& getOverlapParticleWorld()const = 0;
    virtual fj::OverlapParticleWorld* getOverlapParticleWorldPtr() = 0;
};

#endif /* algorithm_hpp */
