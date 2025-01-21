/**
 * @file <src/modules/AutoMoDeBehaviourReactToColor.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourReactToColor.h"

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor::AutoMoDeBehaviourReactToColor() {
        m_strLabel = "ReactToColor";
    }

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor::AutoMoDeBehaviourReactToColor(AutoMoDeBehaviourReactToColor* pc_behaviour) {
        m_strLabel = pc_behaviour->GetLabel();
        m_bLocked = pc_behaviour->IsLocked();
        m_bOperational = pc_behaviour->IsOperational();
        m_unIndex = pc_behaviour->GetIndex();
        m_unIdentifier = pc_behaviour->GetIdentifier();
        m_mapParameters = pc_behaviour->GetParameters();
        Init();
    }

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor* AutoMoDeBehaviourReactToColor::Clone() {
        return new AutoMoDeBehaviourReactToColor(this);
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::ControlStep() {
        CVector2 sColVectorSum, sProxVectorSum, sResultVector;

        // set up a variable to decide which blobs to consider and whether to communicate
        bool specificColor = m_iReactionType == APPROACH_COLOR || m_iReactionType == FLEE_COLOR;
        bool signalFlag = false;

        CColor c = GetColorParameter(m_cColorReceiverParameter, true);
        for (auto it : m_pcRobotDAO->GetCameraInput().BlobList) {
            // skip blobs that are too near or different from the desired color
            bool skipBlob = it->Distance < 6.0;
            skipBlob |= specificColor && it->Color != c;

            // if the blob is considered, update the direction vector (see Vector Field approach)
            if (! skipBlob) {
                sColVectorSum += CVector2(1 / (it->Distance + 1), it->Angle);

                // if the action is "approach", set a communication with the blob
                signalFlag = m_iReactionType == APPROACH_COLOR || m_iReactionType == APPROACH_ANY;
            }
        }

        // according to the robot capabilities, find a direction vector that avoids obstacles
        if (m_bBasicPerceptionCapabilities) {
            for (auto value : m_pcRobotDAO->GetProximityInput()) {
                sProxVectorSum += CVector2(value.Value, value.Angle.SignedNormalize());
            }
        }
        else {
            sProxVectorSum = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);
        }

        if (sColVectorSum.Length() < 0.05) {
            sColVectorSum = CVector2();
        }
        if (sProxVectorSum.Length() < 0.05) {
            sProxVectorSum = CVector2();
        }

        sResultVector = sColVectorSum - sProxVectorSum;

        // if the reaction strategy is flee (0 or 1), then goes in the opposite direction
        if (m_iReactionType <= 1) {
            sResultVector = - sResultVector;
        }

        // react to the color with a specific speed (regardless of the calculated one)
        sResultVector = CVector2(m_unReactionParameter, sResultVector.Angle());

        // set the output of the robot according to the calculated trajectory
        m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));
        m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);
        m_pcRobotDAO->SetRangeAndBearingMessageToSend(signalFlag);

        m_bLocked = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Init() {
        m_iReactionType = FindParameter("crt");
        m_unReactionParameter = FindParameter("vel");
        m_cColorReceiverParameter = FindParameter("clr");

        if (HasParameter("cle")) {
			auto color = GetColorParameter(FindParameter("cle"), true);
			m_cColorEmitterParameter = color;
		}
		else {
			auto color = GetColorParameter(0, true);
			m_cColorEmitterParameter = color;
		}
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Reset() {
        m_bOperational = false;
        ResumeStep();
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::ResumeStep() {
        m_bOperational = true;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Adapt(Real reward) {
        m_iReactionType.Adapt(reward);
        m_unReactionParameter.Adapt(reward);
        m_cColorReceiverParameter.Adapt(reward);
    }

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourReactToColor::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		AutoMoDeBehaviour::SetRobotDAO(pc_robot_dao);
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}
}
