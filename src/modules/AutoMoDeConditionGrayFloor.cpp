/**
 * @file <src/modules/AutoMoDeConditionGrayFloor.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionGrayFloor.h"

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionGrayFloor::AutoMoDeConditionGrayFloor() {
		m_strLabel = "GrayFloor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionGrayFloor::~AutoMoDeConditionGrayFloor() {}

	/****************************************/
	/****************************************/

	AutoMoDeConditionGrayFloor::AutoMoDeConditionGrayFloor(AutoMoDeConditionGrayFloor* pc_condition) {
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

	AutoMoDeConditionGrayFloor* AutoMoDeConditionGrayFloor::Clone() {
		return new AutoMoDeConditionGrayFloor(this);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionGrayFloor::Verify() {
		// according to the robot capabilities, verify if the ground is gray
		bool grayPerceived = m_fGroundThresholdRange.WithinMinBoundExcludedMaxBoundExcluded(
			m_bBasicPerceptionCapabilities
				? m_pcRobotDAO->GetGroundInput().Center
				: m_pcRobotDAO->GetGroundReading()
		);

		// if the ground is gray, the transition depends on the sampled value
		return grayPerceived && EvaluateBernoulliProbability(m_fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionGrayFloor::Init() {
		m_fGroundThresholdRange.Set(0.1, 0.95);
		m_fProbability = FindParameter("p");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionGrayFloor::Reset() {}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionGrayFloor::Adapt(Real reward) {
		m_fProbability.Adapt(reward);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionGrayFloor::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		AutoMoDeCondition::SetRobotDAO(pc_robot_dao);
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}
}
