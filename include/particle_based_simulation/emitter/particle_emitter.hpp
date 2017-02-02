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

namespace fj {
    template<class T>class SparseGrid;
    class Mesh;
    class ParticleEmitter;
}

namespace Eigen {
    template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
    class Matrix;
    typedef Matrix<float, 3, 1, 0/*Eigen::ColMajor*/, 3/*_Raws*/, 1/*_Cols*/> Vector3f;
}

/// 粒子を発生させる場所を決定する.
/** シミュレーションのシーンを作るために, ある形状になるように粒子を発生させることはよくある.
 * 三角メッシュから構成されるオブジェクトを与えると,
 * その形状を構築するために必要な位置を算出する. */
class fj::ParticleEmitter
{
public:
    ParticleEmitter() = default;
    virtual~ParticleEmitter() = default;
    
    /** 粒子を発生させる場所を決定する.
     * @param triangleMeshVertices */
    fj::SparseGrid<bool> execute(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices, const float gridSize);
    
protected:
    /// 引数で渡されたメッシュを内包するような直方体のグリッドを生成する.
    fj::SparseGrid<bool> generateGrid(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices, const float gridSize)const;
    
    /** @return firstが最大値, secondが最小値となるstd::pair*/
    std::pair<Eigen::Vector3f, Eigen::Vector3f> searchMinMax(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices)const;
};

#endif /* particle_emitter_hpp */
