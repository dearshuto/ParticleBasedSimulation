//
//  algorithm.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/12/13.
//
//

#ifndef algorithm_hpp
#define algorithm_hpp

#include <memory>
#include <vector>
#include "particle_based_simulation/additional/additional_procedure.hpp"

namespace fj {
    class SimulationTimeProfile;
    class Algorithm;
}

/// シミュレータの最高クラス
/** とりあえずシミュレーションの流れをテンプレート化してる.  */
class fj::Algorithm
{
protected:
    Algorithm()
    : m_simulationStep(0)
    {
        
    }
public:
    virtual~Algorithm() = default;
    
    /** @brief 指定した時間幅でシミュレーションを進める
     * @param timestep 進める時間幅 */
    void stepSimulation(const float timestep);

    /** シミュレーションの終了処理. 呼ばなくてもメモリリークは起きない. */
    void terminate();
    
    /** シミュレーション時間のプロファイラを作成する. */
    fj::SimulationTimeProfile*const setupSimulationTimeProfileSystem();

protected:
    /** 追加処理を追加する.
     * @pre プロファイルが fj::SimulationProfile::Priority 順に並んでいる.
     * @post プロファイルが fj::SimulationProfile::Priority 順に並んでいる. */
    void addProfileSystem(std::unique_ptr<fj::AdditionalProcedure> additionalProcedure);
    
private:
    void startProfiling();
    
    /** 実際にシミュレーション処理をするのはこの関数. */
    virtual void execute(const float timestep) = 0;
    
    void endProfiling();
public:
    unsigned int getSimulationStep()const
    {
        return m_simulationStep;
    }
protected:
    std::vector<std::unique_ptr<fj::AdditionalProcedure>>* getAdditionalProceduresPtr()
    {
        return &m_additionalProcedures;
    }
private:
    /** fj::Algorithm::stepSimulation を呼んだ回数 */
    unsigned int m_simulationStep;
    
    std::vector<std::unique_ptr<fj::AdditionalProcedure>> m_additionalProcedures;
};

#endif /* algorithm_hpp */
