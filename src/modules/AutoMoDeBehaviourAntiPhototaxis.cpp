/**
 * @file <src/modules/AutoMoDeBehaviourAntiPhototaxis.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourAntiPhototaxis.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis::AutoMoDeBehaviourAntiPhototaxis() {
		m_strLabel = "Anti-Phototaxis";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis::AutoMoDeBehaviourAntiPhototaxis(
		AutoMoDeBehaviourAntiPhototaxis* pc_behaviour
	) : AutoMoDeBehaviour(pc_behaviour) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis::~AutoMoDeBehaviourAntiPhototaxis() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourAntiPhototaxis* AutoMoDeBehaviourAntiPhototaxis::Clone() {
		return new AutoMoDeBehaviourAntiPhototaxis(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviourAntiPhototaxis::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::ControlStep() {
		CVector2 sResultVector(0,CRadians::ZERO);
		CVector2 sLightVector(0,CRadians::ZERO);
		CVector2 sProxVector(0,CRadians::ZERO);

		CCI_EPuckLightSensor::SReading cLightReading = m_pcRobotDAO->GetLightReading();
		sLightVector = CVector2(cLightReading.Value, cLightReading.Angle);

		sProxVector = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);
		sResultVector = -sLightVector - 5*sProxVector;

		if (sResultVector.Length() < 0.1) {
			sResultVector = CVector2(1, CRadians::ZERO);
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::Init() {}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourAntiPhototaxis::ResumeStep() {
		m_bOperational = true;
	}
}
