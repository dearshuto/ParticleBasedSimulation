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

bool fj::Grid::isValid(const Eigen::Vector3f &position)const
{
    // ある値がある範囲内にあるか判定する
    // 境界で不安定にならないように, 等号のときもfalseを返すようにしてある.
    const auto isValidRange = [](const float value, const fj::Grid::Range& range){
        if ((range.Min < value) && ( value < range.Max))
        {
            return true;
        }
        return false;
    };
    
    const bool kHasValidX = isValidRange(position.x(), getRangeX());
    const bool kHasValidY = isValidRange(position.y(), getRangeY());
    const bool kHasValidZ = isValidRange(position.z(), getRangeZ());
    
    return kHasValidX && kHasValidY && kHasValidZ;
}

Eigen::Vector3f fj::Grid::convertIndexToPosition(const Eigen::Index index)const
{
    const auto GridNumX = computeGridNum(getRangeX());
    const auto GridNumY = computeGridNum(getRangeY());
    
    int z = index / (GridNumX * GridNumY);
    int temp = (index - z*GridNumX*GridNumY);
    int y = temp / GridNumX;
    int x = temp - y*GridNumX;
    
    return getGridSize() * Eigen::Vector3f{static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
}

unsigned int fj::Grid::convertPositionToIndex(const Eigen::Vector3f &position)const
{
    // グリッドの最小値をとる点を原点に持ってきたときの相対位置に変換する.
    const float kRelativeMinX = -getRangeX().Min;
    const float kRelativeMinY = -getRangeY().Min;
    const float kRelativeMinZ = -getRangeZ().Min;
    const Eigen::Vector3f kRelativePosition = position + Eigen::Vector3f{kRelativeMinX, kRelativeMinY, kRelativeMinZ};
    const auto kIndexX = std::floor(kRelativePosition.x() / getGridSize());
    const auto kIndexY = std::floor(kRelativePosition.y() / getGridSize());
    const auto kIndexZ = std::floor(kRelativePosition.z() / getGridSize());
    
    return kIndexX
    + computeGridNum(getRangeX()) * kIndexY
    + computeGridNum(getRangeX()) * computeGridNum(getRangeY()) * kIndexZ;
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
    return std::floor((range.Max - range.Min) / getGridSize());
}

Eigen::Vector3i fj::Grid::convertRoundedVector(const Eigen::Vector3f &vector)const
{
    const int kX = std::floor(vector.x());
    const int kY = std::floor(vector.y());
    const int kZ = std::floor(vector.z());
    
    return Eigen::Vector3i{kX, kY, kZ};
}
