#include "AutoMoDeEvaluator.hpp"
#include "AutoMoDeEvaluatorForaging.hpp"

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeEvaluator* AutoMoDeEvaluator::Build(const std::string& type) {
        if (type == "foraging") {
            return new AutoMoDeEvaluatorForaging();
        }
        return new AutoMoDeEvaluator();
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::Init() {}

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::Reset() {}

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::ControlStep() {}

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::NewEvaluation() {}

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluator::CurrentPerformance() {
        return 0;
    }

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluator::CumulativePerformance() {
        return 0;
    }

    /****************************************/
    /****************************************/

    const std::string& AutoMoDeEvaluator::GetLabel() {
        return m_strLabel;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::SetRobotDAO(EpuckDAO* pc_robot_dao) {
        m_pcRobotDAO = pc_robot_dao;
    }
}
