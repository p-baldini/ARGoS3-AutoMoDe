/**
 * @file <src/modules/AutoMoDeConditionBlackFloor.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionBlackFloor.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionBlackFloor::AutoMoDeConditionBlackFloor() {
		m_strLabel = "BlackFloor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionBlackFloor::~AutoMoDeConditionBlackFloor() {}

	/****************************************/
	/****************************************/

	AutoMoDeConditionBlackFloor::AutoMoDeConditionBlackFloor(AutoMoDeConditionBlackFloor* pc_condition) {
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

	void AutoMoDeConditionBlackFloor::Init() {
		m_fGroundThreshold = 0.1;
		m_fProbability = FindParameter("p");
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionBlackFloor* AutoMoDeConditionBlackFloor::Clone() {
		return new AutoMoDeConditionBlackFloor(this);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionBlackFloor::Verify() {
		if (m_pcRobotDAO->GetGroundReading() <= m_fGroundThreshold) {
			return EvaluateBernoulliProbability(m_fProbability);
		}
		else {
			return false;
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionBlackFloor::Reset() {
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionBlackFloor::Adapt(Real reward) {
		m_fProbability.Adapt(reward);
	}
}
