//
//  grid_example.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2017/02/01.
//
//

#include <iostream>
#include "particle_based_simulation/simulation/grid/sparse_grid.hpp"

int main(int argc, char** argv)
{
    fj::SparseGrid<bool> booleanGrid{{1.f, 0.f}, {1.f, 0.f}, {1.f, 0.f}, 0.1};
    const Eigen::Vector3f kTestPosition{0.1, 0.01, 0.01};
    
    if (booleanGrid.isValid(kTestPosition))
        booleanGrid.at(kTestPosition) = true;
    else
        std::cout << "not valid" << std::endl;
    
    for (auto iterator = booleanGrid.iterator(); iterator; ++iterator)
    {
        if(iterator.value())
        {
            std::cout << iterator.index() << ": is non zero!"<< std::endl;
        }
    }
    
    return 0;
}
