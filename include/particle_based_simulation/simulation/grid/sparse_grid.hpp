//
//  sparse_grid.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/02/01.
//
//

#ifndef sparse_grid_hpp
#define sparse_grid_hpp

#include "grid.hpp"

namespace fj {
    template<class T>class SparseGrid;
}

template <class T>
class fj::SparseGrid
{
public:
    SparseGrid() = default;
    virtual~SparseGrid() = default;
};

#endif /* sparse_grid_hpp */
