/**
 * @file <src/modules/AutoMoDeEvaluator.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeEvaluator.hpp"
#include "AutoMoDeEvaluatorForaging.hpp"
#include "AutoMoDeEvaluatorRepair.hpp"

#include <limits>

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeEvaluator* AutoMoDeEvaluator::Build(const std::string& type) {
        if (type == "foraging") {
            return new AutoMoDeEvaluatorForaging();
        }
        if (type == "repair") {
            return new AutoMoDeEvaluatorRepair();
        }
        return new AutoMoDeEvaluator();
    }

    /****************************************/
    /****************************************/

    AutoMoDeEvaluator::AutoMoDeEvaluator() {
        m_uEvaluationTime = std::numeric_limits<UInt32>::max();
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::Init() {
        m_unEvaluationStep = 0;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::Reset() {
        m_unEvaluationStep = 0;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::ControlStep() {
        if (m_unEvaluationStep++ == m_uEvaluationTime) {
            AutoMoDeEvaluator::NewEvaluation();
        }
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::SetEvaluationTime(UInt32 evaluationTime) {
        m_uEvaluationTime = evaluationTime;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluator::NewEvaluation() {
        LOG << "cumulative performance: " << CumulativePerformance() << std::endl;
        m_unEvaluationStep = 0;
    }

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
