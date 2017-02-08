//
//  overlap_particle_shape.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/15.
//
//

#include <algorithm>
#include "particle_based_simulation/simulation/collision_object/particle/overlap_particle_shape.hpp"

std::vector<std::unique_ptr<fj::OverlapParticleShape>> fj::OverlapParticleShape::m_shapes;

fj::OverlapParticleShape*const fj::OverlapParticleShape::GetParticleShape(const float radius, const float bias)
{
    // 半径が1番近いやつを探してくる
    
    // 空だったら問答無用でインスタンス生成
    if (m_shapes.empty())
    {
        return CreateNewInstance(radius);
    }
    
    // アルゴリズムは以下の3ステップ

    // 1.指定された値よりも大きな値が出てくるはじめの要素を探す.
    const int kRequestIsBiggestRadius = -1;
    int kBackIndex = kRequestIsBiggestRadius;

    for (int i = 1; i < m_shapes.size(); ++i)
    {
        if (m_shapes[i]->getRadius() < radius)
        {
            continue;
        }
        else
        {
            kBackIndex = i;
        }
    }
    
    // 指定されてradiusが保持されているどの要素よりも大きかった場合
    if (kBackIndex == kRequestIsBiggestRadius)
    {
        // バイアス内に収まってなかったら新規インスタンスを生成する
        if ((m_shapes.back()->getRadius() - radius) < bias)
        {
            return m_shapes.back().get();
        }
        else{
            return CreateNewInstance(radius);
        }
    }

    // 2. その要素と, 1つ前の要素を比較して, より近いものを探す.
    const int kFrontIndex = kBackIndex - 1;
    
    const float kBackDiff = radius - m_shapes[kFrontIndex]->getRadius();
    const float kFrontDiff = m_shapes[kBackIndex]->getRadius() - radius;
    
    float diff;
    if (kBackDiff < kFrontDiff)
    {
        diff = kBackDiff;
    }
    else
    {
        diff = kFrontDiff;
    }
    
    // 3. バイアスの範囲に収まってたら, 近い方を返す. そうでなかったら新しくインスタンスを生成する.
    if (kBackDiff < bias)
    {
        return m_shapes[kBackIndex].get();
    }
    else
    {
        return CreateNewInstance(radius);
    }
}

fj::OverlapParticleShape*const fj::OverlapParticleShape::CreateNewInstance(const float radius)
{
    fj::OverlapParticleShape* newShape = new fj::OverlapParticleShape(radius);
    m_shapes.push_back(std::unique_ptr<fj::OverlapParticleShape>{newShape});
    //要素を追加したらソートしておくのを忘れずに
    std::sort(std::begin(m_shapes), std::end(m_shapes)
              ,[](const std::unique_ptr<fj::OverlapParticleShape>& particleShape1, const std::unique_ptr<fj::OverlapParticleShape>& particleShape2){
                  return particleShape1->getRadius() < particleShape2->getRadius();
              });
    
    
    return newShape;
}
