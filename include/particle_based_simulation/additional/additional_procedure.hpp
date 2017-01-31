//
//  additional_procedure.hpp
//  CubicFineParticleSimulation
//
//  Created by Shuto Shikama on 2016/10/02.
//
//

#ifndef additional_procedure_hpp
#define additional_procedure_hpp

#include <string>

namespace fj {
    class Algorithm;
    class FineParticleWorld;
    class AdditionalProcedure;
}

/// fj::FineParticleWorld::stepSimulation から呼ばれる処理.
/** シミュレーションのプロファイリングなど, シミュレーションとは直接関係しない処理を提供する. */
class fj::AdditionalProcedure
{
protected:
    enum class Priority : unsigned int
    {
        kI_dont_care,
        kAbsolutelyLast,
    };
public:
    
    AdditionalProcedure(const Priority priority, const std::string& outputDirectory = "./")
    : m_priority(priority)
    , m_outputDirectory(outputDirectory)
    {
        
    }
    virtual ~AdditionalProcedure() = default;
    
     /** シミュレーションを1フレーム進める直前に呼ばれる */
    virtual void startSimulationProfile(const fj::Algorithm& algorithm) = 0;
    
    /** シミュレーションを1フレーム進めた直後に呼ばれる*/
    virtual void endSimulationProfile(const fj::Algorithm& algorithm) = 0;
    
    /** fj::FineParticleWorld::terminate で呼ばれる */
    virtual void terminate() = 0;
    
    /** プロファイリングの途中経過を取得する. フォーマットは特に指定せず, 結果がわかればいいことにします. 
     * @todo 取得文字列のフォーマットも指定できる. テンプレートとか使うんだろうなぁ. */
    virtual std::string getDataAsString()const = 0;
    
    unsigned int getPriorityAdUInt()const
    {
        return static_cast<unsigned int>(m_priority);
    }

    const std::string& getOutputDirectory()const
    {
        return m_outputDirectory;
    }
    
    void setOutputDirectory(const std::string& outputDirectory)
    {
        m_outputDirectory = outputDirectory;
    }
private:
    
    const Priority m_priority;
    
    std::string m_outputDirectory;
};

#endif /* additional_procedure_hpp */
