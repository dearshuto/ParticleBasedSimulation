//
//  particle_emitter.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/31.
//
//

#include <algorithm>
#include <functional>
#include <numeric>
#include <tuple>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "particle_based_simulation/simulation/collision_object/mesh/mesh.hpp"
#include "particle_based_simulation/simulation/grid/sparse_grid.hpp"
#include "particle_based_simulation/emitter/particle_emitter.hpp"

fj::SparseGrid<bool> fj::ParticleEmitter::execute(const std::vector<std::array<Eigen::Vector3f, 3>> &triangleMeshVertices, const float gridSize)
{
    auto grid = generateGrid(triangleMeshVertices, gridSize);
    
    for (auto& vertices: triangleMeshVertices)
    {
        
    }
    return grid;
}

fj::SparseGrid<bool> fj::ParticleEmitter::generateGrid(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices, const float gridSize)const
{
    const auto kMinMax = searchMinMax(triangleMeshVertices);
    const auto& kMax = kMinMax.first;
    const auto& kMin = kMinMax.second;
    
    return {{kMax.x(), kMin.x()}, {kMax.y(), kMin.y()}, {kMax.z(), kMin.z()}, gridSize};
}

std::pair<Eigen::Vector3f, Eigen::Vector3f> fj::ParticleEmitter::searchMinMax(const std::vector<std::array<Eigen::Vector3f, 3> > &triangleMeshVertices)const
{
    // 渡された値が空だった場合は, 無効な値としてゼロベクトルを返すことにする.
    // 無限大を返すと, generateGrid メソッドで無限大の大きさのグリッドが定義されてしまうため.
    if (triangleMeshVertices.empty())
    {
        return {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    }
    
    //まず, 三角メッシュの中の最小値と最大値を見つけてくる
    const float kInfinity = std::numeric_limits<float>::infinity();
    
    // 最大値を格納する方はすべてを負の無限大で, 最小値を格納する方は生の無限大で初期化.
    std::pair<Eigen::Vector3f, Eigen::Vector3f> result{{-kInfinity, -kInfinity, -kInfinity}, {kInfinity, kInfinity, kInfinity}};
    
    // Compare順になってなかったら値を更新する.
    const auto UpdateIf = [](const float value, float* result, const std::function<bool(const float, const float)> compare){
        if (compare(value, *result)) (*result) = value;
    };

    for (const auto& triangle : triangleMeshVertices)
    {
        for (const auto& vertex : triangle)
        {
            for (int i = 0; i < 3; i++)
            {
                // (左辺 > 右辺) が成り立っているときに値を更新する.
                UpdateIf(vertex[i], &result.first[i], std::greater<float>());
                
                // (左辺 < 右辺) が成り立っているときに値を更新する.
                UpdateIf(vertex[i], &result.second[i], std::less<float>());
            }
        }
    }
    
    return result;
}
