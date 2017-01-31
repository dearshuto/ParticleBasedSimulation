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
#include <Eigen/Geometry>
#include "particle_based_simulation/simulation/collision_object/mesh/mesh.hpp"
#include "particle_based_simulation/emitter/particle_emitter.hpp"

void fj::ParticleEmitter::execute(const std::vector<std::array<Eigen::Vector3f, 3>> &triangleMeshVertices, const unsigned int resolution)
{
    for (auto& vertices: triangleMeshVertices)
    {
        
    }
}

Eigen::Array<bool, Eigen::Dynamic, 1/*cols*/> fj::ParticleEmitter::generateBoundingBox(const std::vector<std::array<Eigen::Vector3f, 3>>& triangleMeshVertices)const
{
    // 2つのベクトルに対して, どの要素で比較するかで使い分けるファンクタ
    const CompareFunc CompareX = [](const Eigen::Vector3f& vertex1, const Eigen::Vector3f& vertex2){
        return vertex1.x() < vertex2.x();
    };
    const CompareFunc CompareY = [](const Eigen::Vector3f& vertex1, const Eigen::Vector3f& vertex2){
        return vertex1.y() < vertex2.y();
    };
    const CompareFunc CompareZ = [](const Eigen::Vector3f& vertex1, const Eigen::Vector3f& vertex2){
        return vertex1.z() < vertex2.z();
    };

    const auto kMinMaxX = searchMinMax(triangleMeshVertices, CompareX);
    const auto kMinMaxY = searchMinMax(triangleMeshVertices, CompareY);
    const auto kMinMaxZ = searchMinMax(triangleMeshVertices, CompareZ);

    Eigen::Array<bool, Eigen::Dynamic, 1/*cols*/> boundingBox = Eigen::Array<bool, 10, 1/*cols*/>::Zero();
    return boundingBox;
}

std::pair<Eigen::Vector3f, Eigen::Vector3f> fj::ParticleEmitter::searchMinMax(const std::vector<std::array<Eigen::Vector3f, 3> > &triangleMeshVertices, const CompareFunc &compareFunc)const
{
    // 3つのベクトルをある要素で比較して, 最大値と最小値を求める.
    const auto minmaxIn3Vertecies = [](const std::array<Eigen::Vector3f, 3>& triangleMesh, const CompareFunc& compare){
        return std::minmax<Eigen::Vector3f>(*std::begin(triangleMesh), *std::end(triangleMesh), compare);
    };
    
    const auto kInfinity = std::numeric_limits<float>::infinity();
    std::pair<Eigen::Vector3f, Eigen::Vector3f> minmax = std::make_pair(Eigen::Vector3f{kInfinity, kInfinity, kInfinity}
                                                                        , Eigen::Vector3f{-kInfinity, -kInfinity, -kInfinity});
    
    //まず, 三角メッシュの中の最小値と最大値を見つけてくる
    std::vector<std::pair<Eigen::Vector3f, Eigen::Vector3f>> result;
    for (const auto triangle : triangleMeshVertices)
    {
        result.push_back(minmaxIn3Vertecies(triangle, compareFunc));
    }
    
    // 次に全体を検索して, 最大値と最小値を探す
    for (const auto& pair : result)
    {
        // left < right で比較
        if (compareFunc(minmax.first, pair.first)) {
            minmax.first = pair.first;
        }
        if (compareFunc(pair.second, minmax.second)) {
            minmax.second = pair.second;
        }
    }

}
