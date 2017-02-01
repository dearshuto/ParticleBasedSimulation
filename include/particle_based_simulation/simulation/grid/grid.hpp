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
    typedef Matrix<int, 3, 1> Vector3i;
}

/// 正方形の格子が集まった正方形のグリッド
class fj::Grid
{
protected:
    struct Range
    {
        float Max;
        float Min;
    };

    /// すべてのRangeはsizeよりも大きな値をであること
    Grid(const Range& rangeX, const Range& rangeY, const Range& rangeZ, const float size = 1.0)
    : m_rangeX(rangeX)
    , m_rangeY(rangeY)
    , m_rangeZ(rangeZ)
    , m_gridSize(size)
    {
        
    }

public:
    Grid() = delete;
    virtual~Grid() = default;
    
    bool isValid(const Eigen::Vector3f& position)const;
protected:
        
    unsigned int convertPositionToIndex(const Eigen::Vector3f& position)const;
    
    /// グリッドの講師の数を計算する
    unsigned int computeAllDataSize()const;
    
    /// Rangeにいくつの格子が存在するかを計算する.
    /** @param range getrRangeX(), getRangeY(), getRangeZ() のどれか */
    unsigned int computeGridNum(const Range& range)const;
    
    /// すべての要素を整数型に丸め込んだベクトルを生成する.
    Eigen::Vector3i convertRoundedVector(const Eigen::Vector3f& vector)const;
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
    
    float getGridSize()const
    {
        return m_gridSize;
    }
private:
    Range m_rangeX;
    Range m_rangeY;
    Range m_rangeZ;
    float m_gridSize;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif /* grid_hpp */
