//
//  grid.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#include <cmath>
#include <Eigen/Core>
#include "particle_based_simulation/simulation/grid/grid.hpp"

unsigned int fj::Grid::convertPositionToIndex(const Eigen::Vector3f &position)const
{
    return 0;
}

unsigned int fj::Grid::computeAllDataSize()const
{
    const unsigned int kSizeX = std::floor(getRangeX().Max) - std::floor(getRangeX().Min);
    const unsigned int kSizeY = std::floor(getRangeY().Max) - std::floor(getRangeY().Min);
    const unsigned int kSizeZ = std::floor(getRangeZ().Max) - std::floor(getRangeZ().Min);
    
    return kSizeX * kSizeY * kSizeZ * std::pow< float>(getResolution(), 3);
}
