//
//  additional_procedure.h
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2016/10/10.
//
//

#ifndef additional_procedure_h
#define additional_procedure_h

namespace shkm {
    class AdditionalProcedure;
}

class shkm::AdditionalProcedure
{
public:
    AdditionalProcedure() = default;
    virtual~AdditionalProcedure() = default;
    
    bool initialize();
    
    virtual void runBeforeStepSimulation(const float timestep) = 0;
    
    virtual void runAfterStepSimulation(const float timestep) = 0;
    
    void terminate();
};

#endif /* additional_procedure_h */
