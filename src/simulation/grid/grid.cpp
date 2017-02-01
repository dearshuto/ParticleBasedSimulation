//
//  grid.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#include <cmath>
#include <iostream>
#include <Eigen/Core>
#include "particle_based_simulation/simulation/grid/grid.hpp"

unsigned int fj::Grid::convertPositionToIndex(const Eigen::Vector3f &position)const
{
    // グリッドの最小値をとる点を原点に持ってきたときの相対位置に変換する.
    const float kRelativeMinX = -getRangeX().Min;
    const float kRelativeMinY = -getRangeY().Min;
    const float kRelativeMinZ = -getRangeZ().Min;
    const auto kRelativePosition = position + Eigen::Vector3f{kRelativeMinX, kRelativeMinY, kRelativeMinZ};
    const auto kRoundedRelativePosition = convertRoundedVector(kRelativePosition);

    return kRoundedRelativePosition.x()
    + computeGridNum(getRangeX()) * kRoundedRelativePosition.y()
    + computeGridNum(getRangeX()) * computeGridNum(getRangeY()) * kRoundedRelativePosition.z();
}

unsigned int fj::Grid::computeAllDataSize()const
{
    const unsigned int kSizeX = computeGridNum(getRangeX());
    const unsigned int kSizeY = computeGridNum(getRangeY());
    const unsigned int kSizeZ = computeGridNum(getRangeZ());
    
    return kSizeX * kSizeY * kSizeZ;
}

unsigned int fj::Grid::computeGridNum(const fj::Grid::Range &range)const
{
    return getResolution() * std::floor(range.Max) - std::floor(range.Min);
}

Eigen::Vector3i fj::Grid::convertRoundedVector(const Eigen::Vector3f &vector)const
{
    const int kX = std::floor(vector.x());
    const int kY = std::floor(vector.y());
    const int kZ = std::floor(vector.z());
    
    return Eigen::Vector3i{kX, kY, kZ};
}
