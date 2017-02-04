//
//  mohr_stress_circle.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/11.
//
//

#ifndef mohr_stress_circle_hpp
#define mohr_stress_circle_hpp

#include <array>
#include <tuple>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle.hpp"
#include "particle_based_simulation/shape_2d/circle.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/warren_spring_curve.hpp"

namespace fj {
    class YieldParticle;
    class CollapseCurve;
    class MohrStressCircle;
}

/** モール応力円 */
class fj::MohrStressCircle : public fj::Circle
{
    typedef fj::Circle Super;
    typedef std::vector<btVector3> ContactForceContainer;
    typedef std::vector<btScalar> NormalStressContainer;
public:
    // ShapeTypeを指定させたいので, デフォルトコンストラクタは抹消する.
    // delete修飾子だと宣言は残ってしまうらしく, コンパイルエラーが起きるのでコメントアウトで対応してます.
    MohrStressCircle() = default;
    ~MohrStressCircle() = default;
    
    
    /// @param normalStress 有限な値である力*/
    void addContactForce(const btVector3& normalStress);
    
    /// モール応力円の中心と半径を再計算する.*/
    void rebuildMohrCircle(const fj::YieldParticle& yieldParticle, const btQuaternion& rotateMatrix);
    
    /// 崩壊曲線と交点をもつかを判定する
    bool hasContactPoint(const fj::CollapseCurve& collapseCurve)const;
    
    const Position2D& getCenter()const
    {
        return Super::Center;
    }
    
    const btScalar getRadius()const
    {
        return Super::Radius;
    }
    
private:
    void rebuildCircleCenterAndRadius(const fj::YieldParticle& yieldParticle, const btQuaternion& rotateMatrix);
};

#endif /* mohr_stress_circle_hpp */
