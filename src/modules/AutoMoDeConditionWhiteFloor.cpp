/**
 * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionWhiteFloor.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionWhiteFloor::AutoMoDeConditionWhiteFloor() {
		m_strLabel = "WhiteFloor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionWhiteFloor::~AutoMoDeConditionWhiteFloor() {}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionWhiteFloor::Verify() {
		if (m_pcRobotDAO->GetGroundReading() >= m_fGroundThreshold) {
			return EvaluateBernoulliProbability(m_fProbability);
		}
		else {
			return false;
		}
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionWhiteFloor::AutoMoDeConditionWhiteFloor(AutoMoDeConditionWhiteFloor* pc_condition) {
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

	AutoMoDeConditionWhiteFloor* AutoMoDeConditionWhiteFloor::Clone() {
		return new AutoMoDeConditionWhiteFloor(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::Init() {
		m_fGroundThreshold = 0.95;
		m_fProbability = FindParameter("p");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::Reset() {}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::Adapt(Real reward) {
		m_fProbability.Adapt(reward);
	}
}
