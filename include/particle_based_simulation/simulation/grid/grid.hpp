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
    /// 最大値と最小値のペアを明示して使用するための構造体.
    struct Range
    {
        float Max;
        float Min;
    };

    /**
     * @param size 格子1つの大きさ
     * @note すべてのRangeはsizeよりも大きな範囲ををであること. */
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
    
    /** 指定した位置にグリッドが用意されているか判断する.
     * @param アクセスしたい位置.
     * @return falseのとき, position の位置にある格子にアクセスしようとするとぬるぽで落ちる. */
    bool isValid(const Eigen::Vector3f& position)const;
    
    /** グリッドの内部は1次元の配列として扱われているので, インデックスで指定された格子の3次元空間を取得する. */
    Eigen::Vector3f convertIndexToPosition(const Eigen::Index index)const;
    
    unsigned int convertPositionToIndex(const Eigen::Vector3f& position)const;
    
protected:
    
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
