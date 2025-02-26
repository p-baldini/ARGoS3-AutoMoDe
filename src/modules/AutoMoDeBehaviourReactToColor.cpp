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

	AutoMoDeBehaviourReactToColor::AutoMoDeBehaviourReactToColor(
		AutoMoDeBehaviourReactToColor* pc_behaviour
	) : AutoMoDeBehaviour(pc_behaviour) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourReactToColor* AutoMoDeBehaviourReactToColor::Clone() {
		return new AutoMoDeBehaviourReactToColor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviourReactToColor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "crt=" << m_iReactionType << std::endl;
		ss << "vel=" << m_unReactionParameter << std::endl;
		ss << "clr=" << m_cColorReceiverParameter << std::endl;
		ss << "cle=" << m_cColorEmitterParameter << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourReactToColor::ControlStep() {
		CVector2 sColVectorSum, sProxVectorSum, sResultVector;

		// set up a variable to decide which blobs to consider and whether to communicate
		bool specificColor = (UInt8) m_iReactionType == APPROACH_COLOR || (UInt8) m_iReactionType == FLEE_COLOR;
		bool signalFlag = false;

		for (auto it : m_pcRobotDAO->GetCameraInput().BlobList) {
			// skip blobs that are too near or different from the desired color
			bool skipBlob = it->Distance < 6.0;
			skipBlob |= specificColor && it->Color != (CColor) m_cColorReceiverParameter;

			// if the blob is considered, update the direction vector (see Vector Field approach)
			if (! skipBlob) {
				sColVectorSum += CVector2(1 / (it->Distance + 1), it->Angle);

				// if the action is "approach", set a communication with the blob
				signalFlag = (UInt8) m_iReactionType == APPROACH_COLOR || (UInt8) m_iReactionType == APPROACH_ANY;
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

		if (sColVectorSum.Length() < 0.03) {
			sColVectorSum = CVector2();
		}
		if (sProxVectorSum.Length() < 0.03) {
			sProxVectorSum = CVector2();
		}

		sResultVector = sColVectorSum - (1 - m_unDesireParameter) * sProxVectorSum;

		// if the reaction strategy is flee (0 or 1), then goes in the opposite direction
		if ((UInt8) m_iReactionType <= 1) {
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
		m_iReactionType = m_Parameters->GetParameter<UInt8>("crt", m_unIndex);
		m_unReactionParameter = m_Parameters->GetParameter<Real>("vel", m_unIndex, "12");
		m_unDesireParameter = m_Parameters->GetParameter<Real>("des", m_unIndex, "0");
		m_cColorReceiverParameter = m_Parameters->GetParameter<CColor>("clr", m_unIndex);
		m_cColorEmitterParameter = m_Parameters->GetParameter<CColor>("cle", m_unIndex, "0");
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
