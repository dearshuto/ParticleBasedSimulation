//
//  grid.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#ifndef grid_hpp
#define grid_hpp

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace fj {
    class Grid;
}

class fj::Grid
{
public:
    Grid() = delete;
    virtual~Grid() = default;
protected:
    Grid(const Eigen::Vector2f& rangeX, const Eigen::Vector2f& rangeY, const Eigen::Vector2f& rangeZ)
    : m_rangeX(rangeX)
    , m_rangeY(rangeY)
    , m_rangeZ(rangeZ)
    {
        
    }
protected:
    unsigned int convertPositionToIndex(const Eigen::Vector3f& position)const;
    
public:
    const Eigen::Vector2f& getRangeX()const
    {
        return m_rangeX;
    }
    const Eigen::Vector2f& getRangeY()const
    {
        return m_rangeY;
    }
    const Eigen::Vector2f& getRangeZ()const
    {
        return m_rangeZ;
    }

private:
    Eigen::Vector2f m_rangeX;
    Eigen::Vector2f m_rangeY;
    Eigen::Vector2f m_rangeZ;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif /* grid_hpp */
