#ifndef CORE_HMM_H
#define CORE_HMM_H
#include "./../../common/core/Matrix.h"
#include "./../../common/core/Vector.h"
#include <vector>
namespace patrick
{
    template<class Status, class Value>
    class HMM
    {
    private:
        std::vector<Status> possibleStates;
        std::vector<Value> possibleValues;
        Matrix statusProb;
        Matrix valueProb;
        Vector currentDistribution;
    public:
        HMM(std::vector<Status>& possibleStatus, std::vector<Value>& possibleValues)
            : possibleStatus{possibleStatus}, possibleValues{possibleValues}{};
        double probOfValues(Matrix& statusProb, Matrix& valueProb, 
            Vector& initDistribution, std::vector<Value>& values);
        void learnParam(std::vector<Value>& values);
        std::vector<Status> predict(Matrix& statusProb, Matrix& valueProb, 
            Vector& initDistribution, std::vector<Value>& values)
    };
} // namespace patrick

#endif