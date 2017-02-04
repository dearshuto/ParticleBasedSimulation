//
//  discritized_particle_shape.cpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/10.
//
//

#include <array>
#include <algorithm>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "particle_based_simulation/simulation/collision_object/particle/discritized_particle_shape.hpp"

void fj::DiscritizedParticleShape::NormalContainer::addForce(const btVector3 &force)
{
    for (unsigned int i = 0; i < this->size(); i++)
    {
        const btVector3& kNornal = this->get(i);
        const btScalar kPressure =  std::max<btScalar>(0, kNornal.dot(force));
        addAt(kPressure, i);
    }
}

std::unique_ptr<fj::DiscritizedParticleShape::NormalContainer> fj::DiscritizedParticleShape::GetDiscretizedParticleShapeNormal(const ShapeType type)
{
    //---------- 離散化形状を表すクラスの派生の定義 ------------------------------------------------------------------
    
    class CubeNormalContainer : public fj::DiscritizedParticleShape::NormalContainer
    {
    public:
        // コンストラクタ
        CubeNormalContainer()
        : m_normalArray({{
            {1, 0, 0},
            {-1, 0, 0},
            {0, 1, 0},
            {0, -1, 0},
            {0, 0, 1},
            {0, 0, -1}
        }})
        {}
        
        ~CubeNormalContainer() = default;
        
        unsigned int size()const override
        {
            return static_cast<unsigned int>(m_normalArray.size());
        }
        
        const btVector3& get(unsigned int index)const override
        {
            return m_normalArray[index];
        }
        
        void rotate(const btMatrix3x3& matrix)override
        {
            std::for_each(m_normalArray.begin(), m_normalArray.end()
                          , [matrix](btVector3& vector){
                              vector = matrix * vector;
                          });
        }
        void addAt(const float pressure, const unsigned int index)override
        {
            m_force[index] += pressure;
        }
    private:
        std::array<btVector3, 6> m_normalArray;
        std::array<float, 6> m_force;
    };
    
    
    
    
    //---------- インスタンス選択 ------------------------------------------------------------------------------------

    return std::unique_ptr<CubeNormalContainer>(new CubeNormalContainer());
}
