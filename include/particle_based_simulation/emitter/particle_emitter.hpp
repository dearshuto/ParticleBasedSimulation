//
//  particle_emitter.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/31.
//
//

#ifndef particle_emitter_hpp
#define particle_emitter_hpp

#include <array>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/StdVector>

namespace fj {
    class Mesh;
    class ParticleEmitter;
}

/// 粒子を発生させる場所を決定する.
/** シミュレーションのシーンを作るために, ある形状になるように粒子を発生させることはよくある.
 * 三角メッシュから構成されるオブジェクトを与えると,
 * その形状を構築するために必要な位置を算出する. */
class fj::ParticleEmitter
{
    typedef std::function<bool(const Eigen::Vector3f& vertex1, const Eigen::Vector3f& vertex2)> CompareFunc;
private:
    ParticleEmitter() = default;
public:
    virtual~ParticleEmitter() = default;
    
    /** 粒子を発生させる場所を決定する.
     * @param triangleMeshVertices */
    void execute(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices, const unsigned int resolution);
    
protected:
    Eigen::Array<bool, Eigen::Dynamic, 1/*cols*/> generateBoundingBox(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices)const;
    
    std::pair<Eigen::Vector3f, Eigen::Vector3f> searchMinMax(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices, const CompareFunc& compareFunc)const;
    
public:
    const std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>>& getEmittPosition()const
    {
        return m_positions;
    }
private:
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>> m_positions;
};

#endif /* particle_emitter_hpp */
