//
//  grid.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#ifndef grid_hpp
#define grid_hpp

namespace fj {
    class Grid;
}

namespace Eigen {
    typedef Matrix<float, 3, 1> Vector3f;
}

class fj::Grid
{
protected:
    struct Range
    {
        float Max;
        float Min;
    };
public:
    Grid() = delete;
    virtual~Grid() = default;
protected:
    Grid(const Range& rangeX, const Range& rangeY, const Range& rangeZ, const float resolution = 1.0)
    : m_rangeX(rangeX)
    , m_rangeY(rangeY)
    , m_rangeZ(rangeZ)
    , m_resolution(resolution)
    {
        
    }
protected:
    unsigned int convertPositionToIndex(const Eigen::Vector3f& position)const;
    
    unsigned int computeAllDataSize()const;
    
public:
    const Range& getRangeX()const
    {
        return m_rangeX;
    }
    const Range& getRangeY()const
    {
        return m_rangeY;
    }
    const Range& getRangeZ()const
    {
        return m_rangeZ;
    }
    
    unsigned int getResolution()const
    {
        return m_resolution;
    }
private:
    Range m_rangeX;
    Range m_rangeY;
    Range m_rangeZ;
    unsigned int m_resolution;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif /* grid_hpp */
