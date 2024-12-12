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

    void AutoMoDeEvaluatorForaging::Init() {
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
        m_bHasPrey = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::Reset() {
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
        m_bHasPrey = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorForaging::ControlStep() {
        Real groundColor = m_pcRobotDAO->GetGroundInput().Center;

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
