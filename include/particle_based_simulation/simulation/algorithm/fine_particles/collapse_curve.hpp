//
//  collapse_curve.hpp
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/09.
//
//

#ifndef collapse_curve_hpp
#define collapse_curve_hpp

#include "particle_based_simulation/shape_2d/math_function_c2.hpp"

namespace fj {
    class CollapseCurve;
}

/// 粉体崩壊曲線
class fj::CollapseCurve : public fj::MathFunctionC2
{
protected:
    CollapseCurve() = default;
public:
    virtual~CollapseCurve() = default;
};

#endif /* collapse_curve_hpp */
