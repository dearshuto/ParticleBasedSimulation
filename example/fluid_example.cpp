//
//  fluid_example.cpp
//  RayTracer
//
//  Created by Shuto Shikama on 2016/08/02.
//
//

#include <iostream>
#include "particle_based_simulation/world/fluid_world.hpp"

int main(int argc, char** argv)
{
    shkm::FluidWorld fluidWorld;
    
    auto particle = fluidWorld.generateParticle( shkm::Vector3() );
    fluidWorld.stepSimulation(1.0/60.0);
    
    return EXIT_SUCCESS;
}
