/**
 * @file <src/modules/AutoMoDeBehaviourStop.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourStop.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop::AutoMoDeBehaviourStop() {
		m_strLabel = "Stop";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop::AutoMoDeBehaviourStop(
		AutoMoDeBehaviourStop* pc_behaviour
	) : AutoMoDeBehaviour(pc_behaviour) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop::~AutoMoDeBehaviourStop() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop* AutoMoDeBehaviourStop::Clone() {
		return new AutoMoDeBehaviourStop(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviourStop::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "cle=" << m_cColorEmitterParameter << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::ControlStep() {
		m_pcRobotDAO->SetWheelsVelocity(0,0);
		m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::Init() {
		m_cColorEmitterParameter = m_Parameters->GetParameter<CColor>("cle", m_unIndex, "0");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourStop::ResumeStep() {
		m_bOperational = true;
	}
}
