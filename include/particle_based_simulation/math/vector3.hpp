//
//  vector3.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef vector3_hpp
#define vector3_hpp

namespace shkm {
    class Vector3;
}

class shkm::Vector3
{
public:
    Vector3()
    : Vector3(0, 0, 0)
    {
        
    }
    
    virtual~Vector3() = default;
    
    Vector3(const float x, const float y, const float z)
    {
        
    }
};

#endif /* vector3_hpp */
