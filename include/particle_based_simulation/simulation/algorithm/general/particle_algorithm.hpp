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
    class POVRayOutput;
    class ParticleAlgorithm;
}

/// 粒子のオーバーラップを検出するワールドへのインタフェース
class fj::ParticleAlgorithm : public fj::Algorithm
{
public:
    ParticleAlgorithm() = default;
    virtual~ParticleAlgorithm() = default;
    
    
    /** POV-Ray形式でシーンを出力するシステムを作成する. この関数を複数回呼んだときの挙動は未定義.
     * @return 作成したシステムへのポインタ. */
    std::weak_ptr<fj::POVRayOutput> setupPOVRaySceneOutputSystem();
    
    virtual const fj::OverlapParticleWorld& getOverlapParticleWorld()const = 0;
    virtual fj::OverlapParticleWorld* getOverlapParticleWorldPtr() = 0;
};

#endif /* algorithm_hpp */
