//
//  sparse_grid.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#ifndef sparse_grid_hpp
#define sparse_grid_hpp

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET

#include <Eigen/SparseCore>
#include "grid.hpp"

namespace fj {
    template<class T>class SparseGrid;
}

template <class T>
class fj::SparseGrid : public fj::Grid
{
    typedef fj::Grid Super;
public:
    SparseGrid() = default;
    virtual~SparseGrid() = default;
    
    SparseGrid(const Range& rangeX, const Range& rangeY, const Range& rangeZ)
    : Super(rangeX, rangeY, rangeZ)
    {
        m_data.resize(computeAllDataSize());
    }
    
    typename Eigen::SparseVector<T>::InnerIterator iterator()const
    {
        return Eigen::SparseVector<bool>::InnerIterator{m_data};
    }
    
    const T& at(const Eigen::Vector3f& position)const
    {
        return m_data.coeffRef(convertPositionToIndex(position));
    }
    T& at(const Eigen::Vector3f& position)
    {
        return m_data.coeffRef(convertPositionToIndex(position));
    }

private:
    Eigen::SparseVector<T> m_data;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif /* sparse_grid_hpp */
