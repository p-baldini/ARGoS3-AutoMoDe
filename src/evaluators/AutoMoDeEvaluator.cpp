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

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

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

    AutoMoDeEvaluator::~AutoMoDeEvaluator() { }

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
        if (++m_unEvaluationStep >= m_uEvaluationTime) {
            NewEvaluation();
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
        m_bBasicPerceptionCapabilities = (
            typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
            typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
            typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
            typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
        );
    }
}
