//
//  discritized_particle_shape.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto on 2016/09/10.
//
//

#ifndef discritized_particle_shape_hpp
#define discritized_particle_shape_hpp

#include <memory>
#include <tuple>

class btVector3;
class btMatrix3x3;

namespace fj {
    class DiscritizedParticleShape;
}

/** 粉体粒子を離散化した形状を提供する
 * 離散化形状は法線の集合で表される. */
class fj::DiscritizedParticleShape
{
public:
    enum class ShapeType
    {
        kCube,
    };
    
    class NormalContainer
    {
    public:
        NormalContainer() = default;
        virtual~NormalContainer() = default;
        
        void addForce(const btVector3& force);
        virtual unsigned int size()const = 0;
        virtual const btVector3& get(unsigned int index)const = 0;
        virtual void rotate(const btMatrix3x3& matrix) = 0;
        const std::pair<float, float>& getMinMax();
    private:
        /// i番目の面にかかる圧力を追加する
        virtual void addAt(const float pressure, const unsigned int index) = 0;
        
        // 0->max, 1->min
        std::pair<float, float> m_minmax;
    };

protected:
    DiscritizedParticleShape() = default;
public:
    virtual~DiscritizedParticleShape() = default;

    static std::unique_ptr<fj::DiscritizedParticleShape::NormalContainer> GetDiscretizedParticleShapeNormal(const ShapeType type);
};

#endif /* discritized_particle_shape_hpp */
