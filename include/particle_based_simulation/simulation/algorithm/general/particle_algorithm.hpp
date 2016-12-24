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
    
    
    /** POV-Ray形式でシーンを出力するシステムを作成する.
     * @return 作成したシステムへのポインタ
     * @todo 複数回呼び出すと, 同じ役割のインスタンスが作成されてしまう問題を解決する. */
    fj::POVRayOutput*const setupPOVRaySceneOutputSystem()
    {
        std::unique_ptr<fj::POVRayOutput> povray{new fj::POVRayOutput(getWorld())};
        fj::POVRayOutput*const povrayPointer = povray.get();
        addProfileSystem(std::move(povray));
        return povrayPointer;
    }
    
    
    virtual const fj::OverlapParticleWorld& getOverlapParticleWorld()const = 0;
    virtual fj::OverlapParticleWorld* getOverlapParticleWorldPtr() = 0;
};

#endif /* algorithm_hpp */
