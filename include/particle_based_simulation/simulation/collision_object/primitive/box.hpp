//
//  box.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/10/29.
//
//

#ifndef box_hpp
#define box_hpp

#include "particle_based_simulation/simulation/collision_object/collision_object.hpp"

namespace fj {
    class Box;
}

/// 中心にピボットがある直方体
class fj::Box : public fj::CollisionObject
{
    typedef fj::CollisionObject Super;
public:
    Box() = delete;
    ~Box() = default;
    
    /** 
     * @param size Width, Height, Depth の値. ピボットはキューブの中心
     * @param mass 質量[kg] */
    Box(const btVector3& size, const btScalar mass)
    : Super(mass, std::unique_ptr<btBoxShape>(new btBoxShape(size)))
    {
        
    }
};

#endif /* box_hpp */
