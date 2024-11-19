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

	AutoMoDeBehaviourStop::AutoMoDeBehaviourStop(AutoMoDeBehaviourStop* pc_behaviour) {
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

	AutoMoDeBehaviourStop::~AutoMoDeBehaviourStop() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourStop* AutoMoDeBehaviourStop::Clone() {
		return new AutoMoDeBehaviourStop(this);
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
		m_cColorEmitterParameter = GetColorParameter(FindParameter("cle"), true);
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
