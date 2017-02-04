//
//  mohr_stress_circle.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/11.
//
//

#include <numeric>
#include <vector>
#include "particle_based_simulation/simulation/algorithm/fine_particles/yield_particle.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/mohr_stress_circle.hpp"

void fj::MohrStressCircle::rebuildMohrCircle(const fj::YieldParticle& yieldParticle, const btQuaternion& rotateMatrix)
{
    // 接触力がないときはモールの応力円が定義できないので, 中心が原点で半径が無限大ということにしておく
    // 半径0だと0除算が出てきそうで怖い.
    
    if (yieldParticle.hasContactForce())
    {
        rebuildCircleCenterAndRadius(yieldParticle, rotateMatrix);
    }
    else
    {
        Center = {0.0, 0.0};
        Radius = std::numeric_limits<float>::infinity();
    }
}


void fj::MohrStressCircle::rebuildCircleCenterAndRadius(const fj::YieldParticle& yieldParticle, const btQuaternion& rotateMatrix)
{
    // 各面にかかっている垂直応力の中の最大値と最小値を見つける.
    
    const auto& kMinMax = yieldParticle.getMinMax();
    const auto kMin = std::get<0>(kMinMax);
    const auto kMax = std::get<1>(kMinMax);

    Center = {static_cast<btScalar>(( kMin + kMax) / 2.0), 0};
    Radius = (kMax - kMin) / btScalar(2.);
}

bool fj::MohrStressCircle::hasContactPoint(const fj::CollapseCurve &collapseCurve)const
{
    // とりあえずモールの応力円の中心のx座標で比較することで交差点が存在するかを判定する
    // todo: 任意の曲線と円における最近傍を求める一般的な解法に変える
    
    const auto& kThisCenter = getCenter();
    return collapseCurve.compute(kThisCenter.X) < kThisCenter.Y;
}
