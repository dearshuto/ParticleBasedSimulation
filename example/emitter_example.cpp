//
//  emitter_example.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2017/02/02.
//
//

#include <iostream>
#include <Eigen/Core>
#include "particle_based_simulation/emitter/particle_emitter.hpp"
#include "particle_based_simulation/simulation/grid/sparse_grid.hpp"

int main(int argc, char** argv)
{
    // 適当なさん頂点を使用して三角メッシュを定義する
    std::vector<std::array<Eigen::Vector3f, 3>> triangleMesh;
    std::array<Eigen::Vector3f, 3> array ={{{1.0f, 0.1f, 0.3f}, {0.7f, 0.7f, 0.5f}, {1.4f, 0.3f, 0.6f}}};
    triangleMesh.push_back(array);
    
    // 粒子を発生させる位置をグリッドとして算出
    fj::ParticleEmitter emitter;
    const auto grid = emitter.execute(triangleMesh, 0.1);
    
    // non-zeroのグリッドにアクセスする.
    for (auto iterator = grid.iterator(); iterator; ++iterator)
    {
        const auto index = iterator.index();
        const auto kPosition = grid.convertIndexToPosition(index);
        std::cout << index << ": " <<  kPosition.x() << ", " << kPosition.y() << ", " << kPosition.z() << std::endl;
    }
    
    return 0;
}
