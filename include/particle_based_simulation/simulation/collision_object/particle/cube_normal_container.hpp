//
//  cube_normal_container.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/04.
//
//

#ifndef cube_normal_container_hpp
#define cube_normal_container_hpp

#include "discritized_particle.hpp"

namespace fj {
    class CubeNormalContainer;
}

class fj::CubeNormalContainer : public fj::NormalContainer
{
private:
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
    
public:
    ~CubeNormalContainer() = default;
    
    CubeNormalContainer(const fj::CubeNormalContainer& other) = delete;
    CubeNormalContainer& operator=(const fj::CubeNormalContainer& other) = delete;
    
    static std::shared_ptr<fj::CubeNormalContainer> GetInstance()
    {
        static std::shared_ptr<fj::CubeNormalContainer> instance;
        if (instance) {
            return instance;
        }
        else
        {
            instance.reset(new fj::CubeNormalContainer);
            return instance;
        }
    }
    
    size_t size()const override
    {
        return static_cast<unsigned int>(m_normalArray.size());
    }
    
    const btVector3& get(unsigned int index)const override
    {
        return m_normalArray[index];
    }
    
//    void rotate(const btMatrix3x3& matrix)override
//    {
//        std::for_each(m_normalArray.begin(), m_normalArray.end()
//                      , [matrix](btVector3& vector){
//                          vector = matrix * vector;
//                      });
//    }
private:
    std::array<btVector3, 6> m_normalArray;
};

#endif /* cube_normal_container_hpp */
