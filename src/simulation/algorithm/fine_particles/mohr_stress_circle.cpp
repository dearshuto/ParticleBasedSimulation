//
//  mohr_stress_circle.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/11.
//
//

#include <numeric>
#include <vector>
#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle_shape.hpp"
#include "particle_based_simulation/simulation/algorithm/fine_particles/mohr_stress_circle.hpp"

void fj::MohrStressCircle::addContactForce(const btVector3& normalStress)
{
    m_contactForce.push_back(normalStress);
}

void fj::MohrStressCircle::rebuildMohrCircle(const btQuaternion& rotateMatrix)
{
    // 接触力がないときはモールの応力円が定義できないので, 中心が原点で半径が無限大ということにしておく
    // 半径0だと0除算が出てきそうで怖い.
    
    if (hasContact())
    {
        rebuildCircleCenterAndRadius(rotateMatrix);
    }
    else
    {
        Center = {0.0, 0.0};
        Radius = std::numeric_limits<float>::infinity();
    }
}

bool fj::MohrStressCircle::hasContact()const
{
    return !m_contactForce.empty();
}

void fj::MohrStressCircle::clearContactForce()
{
    m_contactForce.clear();
}

void fj::MohrStressCircle::rebuildCircleCenterAndRadius(const btQuaternion& rotateMatrix)
{
    // 各面にかかっている垂直応力の中の最大値と最小値を見つける.
    
    NormalStressContainer stressContainer = computeNormalStress(rotateMatrix);
    const auto& kMinMax = std::minmax_element(std::begin(stressContainer), std::end(stressContainer));
    const auto kMin = *std::get<0>(kMinMax);
    const auto kMax = *std::get<1>(kMinMax);

    Center = {static_cast<btScalar>(( kMin + kMax) / 2.0), 0};
    Radius = (kMax - kMin) / btScalar(2.);
}

fj::MohrStressCircle::NormalStressContainer fj::MohrStressCircle::computeNormalStress(const btQuaternion &rotateMatrix)const
{
    // 各面に対してかかっている垂直応力を算出する
    
    // 離散化形状
    auto discretizedShape = fj::DiscritizedParticleShape::GetDiscretizedParticleShapeNormal(getDiscretizedShapeType());
    
    // 離散化形状の麺の数だけコンテナを用意して, 0で初期化しておく
    NormalStressContainer stressContainer;
    stressContainer.resize(discretizedShape->size());
    std::fill(stressContainer.begin(), stressContainer.end(), 0);
    
    // 離散化形状の各面の法線に回転成分を適用する. そのあとすべての接触力を評価する
    for (int i = 0; i < discretizedShape->size(); i++)
    {
        auto kNormal = discretizedShape->get(i);//rotateMatrix * discretizedShape->get(i);
//        kNormal *= rotateMatrix.inverse();
        
        for (const auto& stress: m_contactForce)
        {
            stressContainer[i] += std::max( static_cast<btScalar>(0.0), stress.dot({kNormal.x(), kNormal.y(), kNormal.z()}));
        }
    }
    
    return stressContainer;
}

bool fj::MohrStressCircle::hasContactPoint(const fj::CollapseCurve &collapseCurve)const
{
    // とりあえずモールの応力円の中心のx座標で比較することで交差点が存在するかを判定する
    // todo: 任意の曲線と円における最近傍を求める一般的な解法に変える
    
    const auto& kThisCenter = getCenter();
    return collapseCurve.compute(kThisCenter.X) < kThisCenter.Y;
}
