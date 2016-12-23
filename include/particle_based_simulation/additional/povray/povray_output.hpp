//
//  povray_output.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/08/25.
//
//

#ifndef povray_output_hpp
#define povray_output_hpp

#include <memory>
#include "particle_based_simulation/additional/particle_information_profiler.hpp"

namespace fj {
    class FineParticleWorld;
    class POVRayOutput;
}

/** シーンをPOV-Ray形式で出力する.
 * x-z平面に乗っている無限平面と粒子をレンダリングするシーンを出力する. */
class fj::POVRayOutput : public fj::ParticleInformationProfiler
{
private:
    typedef fj::ParticleInformationProfiler Super;
    
    struct Vector3D
    {
        Vector3D()
        : X(0), Y(0), Z(0)
        {
            
        }
        
        double X;
        double Y;
        double Z;
    };
public:
    struct CameraInfomation
    {
        Vector3D Location;
        Vector3D LookAt;
    };
public:
    POVRayOutput(const fj::OverlapParticleWorld& particleWorld, const std::string& outputDirectory = "./")
    : Super(particleWorld, Priority::kI_dont_care)
    {
        
    }

    ~POVRayOutput() = default;
    
    void startSimulationProfile(const fj::Algorithm& algorithm) override;
    
    void endSimulationProfile(const fj::Algorithm& algorithm)  override;
    
    void terminate() override;
    
    /** @copydoc Super::getDataAsString() */
    std::string getDataAsString()const override;
    
    bool saveToFile(const std::string& filename)const;
    
    CameraInfomation* getCameraInformationPtr()
    {
        return &m_cameraInfomation;
    }

    const CameraInfomation& getCameraInformation()const
    {
        return m_cameraInfomation;
    }

private:
    
    CameraInfomation m_cameraInfomation;
};

#endif /* povray_output_hpp */
