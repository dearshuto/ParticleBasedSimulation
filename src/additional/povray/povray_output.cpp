//
//  povray_output.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/08/25.
//
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "particle_based_simulation/simulation/overlap_particle_world.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/rheorogy_algorithm.hpp"
#include "particle_based_simulation/simulation/collision_object/particle/particle.hpp"
#include "particle_based_simulation/additional/povray/povray_output.hpp"

void fj::POVRayOutput::startSimulationProfile(const fj::Algorithm& algorithm)
{
    
}

void fj::POVRayOutput::endSimulationProfile(const fj::Algorithm& algorithm)
{
    const std::string kFilename = std::to_string(algorithm.getSimulationStep()) + ".pov";
    saveToFile(kFilename);
}

void fj::POVRayOutput::terminate()
{
    
}

std::string fj::POVRayOutput::getDataAsString()const
{
    return "";
}

bool fj::POVRayOutput::saveToFile(const std::string &filename)const
{
    std::ofstream output(filename);
    
    if (output.fail())
    {
        std::cout << "cannot open " << filename << std::endl;
        return false;
    }
    
    const auto& kPosition = getCameraInformation().Location;
    const auto& kLookAt = getCameraInformation().LookAt;
    
    std::string POV("");
    POV += "#include\"Colors.inc\"";
    POV += "camera {";
    POV += "   perspective";
    POV +=("    location <"
           + std::to_string(kPosition.X)
           + std::string(",")
           + std::to_string(kPosition.Y)
           + std::string(",")
           + std::to_string(kPosition.Z)
           + std::string(">")
           );
           
    POV += "    angle 60";
    POV += "     up <0,1,0>";
    POV +=("    look_at <"
           + std::to_string(kLookAt.X)
           + std::string(",")
           + std::to_string(kLookAt.Y)
           + std::string(",")
           + std::to_string(kLookAt.Z)
           + std::string(">")
           );
    
    POV += "  }";
    
    
    POV += "light_source{";
    POV +=("<"
           + std::to_string(kPosition.X)
           + std::string(",")
           + std::to_string(kPosition.Y)
           + std::string(",")
           + std::to_string(kPosition.Z)
           + std::string(">")
           );
    POV += "    color 1.0";
    POV += "}";
    
    POV += "sky_sphere{";
    POV += "    pigment{";
    POV += "        gradient y";
    POV += "        color_map{";
    POV += "            [ 0.0 White * 0.9 ]";
    POV += "            [ 1.0 color rgb<0.3,0.4,1.2>]";
    POV += "        }";
    POV += "    }";
    POV += "}";
    
    
    POV += "plane{y,0";
    POV += "    pigment{";
    POV += "        checker White*1.2, color rgb<0.5,0.9,0.9>*10";
    POV += "        scale 10.2";
    POV += "    }";
    POV += "    finish{phong 1 reflection 0.3}";
    POV += "}";
    
    auto iterator = getParticleWorld().iterator();
    
    while (iterator->hasNext())
    {
        const auto& particle = iterator->next();
        const auto position = particle.getPosition();
        POV += "sphere{";

        POV += std::string("<") + std::to_string(position.x()) + "," + std::to_string(position.y()) + "," + std::to_string(position.z()) + std::string(">");
        
        POV += "," + std::to_string(particle.getOverlapRange());
        POV += "    texture{ pigment{ color rgb<1.0, 1.0, 1.0> }}";
        POV += "}";
    }
    
    output << POV;
    
    return true;
}
