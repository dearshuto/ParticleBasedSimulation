//
//  particle_emitter.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/31.
//
//

#ifndef particle_emitter_hpp
#define particle_emitter_hpp

#include <vector>
#include <Eigen/Core>
#include <Eigen/StdVector>

namespace fj {
    class Mesh;
    class ParticleEmitter;
}

/// 粒子の発生を制御する
class fj::ParticleEmitter
{
private:
    ParticleEmitter() = default;
public:
    virtual~ParticleEmitter() = default;
    
    void execute(const fj::Mesh& mesh);
    
    const std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>>& getEmittPosition()const
    {
        return m_positions;
    }
private:
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>> m_positions;
};

#endif /* particle_emitter_hpp */
