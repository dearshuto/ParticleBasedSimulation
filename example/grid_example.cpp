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
    fj::SparseGrid<bool> booleanGrid{{0.f, 1.f}, {0.f, 1.f}, {0.f, 1.f}};
    booleanGrid.at({0, 0, 0}) = true;
    
    for (auto iterator = booleanGrid.iterator(); iterator; ++iterator)
    {
        if(iterator.value())
        {
            std::cout << "non zero!"<< std::endl;
        }
    }

    
    return 0;
}
