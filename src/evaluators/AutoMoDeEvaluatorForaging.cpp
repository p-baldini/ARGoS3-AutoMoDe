/**
 * @file <src/modules/AutoMoDeEvaluatorForaging.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeEvaluatorForaging.hpp"

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeEvaluatorForaging::~AutoMoDeEvaluatorForaging() { }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::Init() {
        AutoMoDeEvaluator::Init();
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
        m_bHasPrey = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::Reset() {
        AutoMoDeEvaluator::Reset();
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
        m_bHasPrey = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::ControlStep() {
        AutoMoDeEvaluator::ControlStep();

        Real groundColor = m_bBasicPerceptionCapabilities
            ? m_pcRobotDAO->GetGroundInput().Center
            : m_pcRobotDAO->GetGroundReading();

        // if the robot perceives white ground and it does not yet has a prey, get one and increase
        // the performance counter.
        if (groundColor > 0.75) {
            m_fCurrentPerformance += m_bHasPrey ? 0 : 1;
            m_bHasPrey = true;
        }
        else
        // if the robot perceives black ground and it has a prey, deposit it and increase the
        // the performance counter.
        if (groundColor < 0.25) {
            m_fCurrentPerformance += m_bHasPrey ? 1 : 0;
            m_bHasPrey = false;
        }
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::NewEvaluation() {
        AutoMoDeEvaluator::NewEvaluation();
        m_fCumulativePerformance += m_fCurrentPerformance;
        m_fCurrentPerformance = 0;
    }

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluatorForaging::CurrentPerformance() {
        return m_fCurrentPerformance;
    }

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluatorForaging::CumulativePerformance() {
        return m_fCumulativePerformance;
    }
}
