//
//  cubic_normal_force_container.cpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#include "particle_based_simulation/simulation/algorithm/fine_particles/cubic_normal_force_container.hpp"

void fj::CubeNormalForceContainer::addStressAt(const float pressure, const unsigned int index)
{
    m_pressure[index] += pressure;
}

void fj::CubeNormalForceContainer::clearStress()
{
    std::fill(std::begin(m_pressure), std::end(m_pressure), static_cast<btScalar>(0));
}

std::pair<btScalar, btScalar> fj::CubeNormalForceContainer::getMinMax()const
{
    return std::minmax(*std::begin(m_pressure), *std::end(m_pressure));
}
