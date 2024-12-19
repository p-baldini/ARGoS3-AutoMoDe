/**
 * @file <src/modules/AutoMoDeConditionFloorColor.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionFloorColor.hpp"

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeConditionFloorColor::AutoMoDeConditionFloorColor() {
        m_strLabel = "FloorColor";
    }

    /****************************************/
    /****************************************/

    AutoMoDeConditionFloorColor::AutoMoDeConditionFloorColor(AutoMoDeConditionFloorColor* pc_condition) {
        m_strLabel = pc_condition->GetLabel();
        m_unIndex = pc_condition->GetIndex();
        m_unIdentifier = pc_condition->GetIndex();
        m_unFromBehaviourIndex = pc_condition->GetOrigin();
        m_unToBehaviourIndex = pc_condition->GetExtremity();
        m_mapParameters = pc_condition->GetParameters();
        Init();
    }

    /****************************************/
    /****************************************/

    AutoMoDeConditionFloorColor* AutoMoDeConditionFloorColor::Clone() {
        return new AutoMoDeConditionFloorColor(this);
    }

    /****************************************/
    /****************************************/

    bool AutoMoDeConditionFloorColor::Verify() {
        Real reading = m_bBasicPerceptionCapabilities
            ? m_pcRobotDAO->GetGroundInput().Center
            : m_pcRobotDAO->GetGroundReading();

        // check if the robot perceives a value in the surrounding of the desired value
        bool perceived = m_fGroundColor - .25 <= reading && reading <= m_fGroundColor + .25;

        // if the condition type is `absence`, negate the presence of the perceived color
        perceived = m_eType == 1 ? ! perceived : perceived;

        // if the ground condition is enabled, check if transition probability
        return perceived && EvaluateBernoulliProbability(m_fProbability);
    }

    /****************************************/
    /****************************************/

    void AutoMoDeConditionFloorColor::Reset() {
        Init();
    }

    /****************************************/
    /****************************************/

    void AutoMoDeConditionFloorColor::Init() {
        m_eType = FindParameter("t");
        m_fGroundColor = FindParameter("v");
        m_fProbability = FindParameter("p");
    }

    /****************************************/
    /****************************************/

    void AutoMoDeConditionFloorColor::Adapt(Real reward) {
        m_fProbability.Adapt(reward);
    }
}
