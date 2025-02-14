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

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

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
		// according to the robot capabilities, verify if the ground is white
		bool whitePerceived = m_bBasicPerceptionCapabilities
			? m_pcRobotDAO->GetGroundInput().Center >= (Real) m_fGroundThreshold
			: m_pcRobotDAO->GetGroundReading() >= (Real) m_fGroundThreshold;

		// if the ground is white, the transition depends on the sampled value
		return whitePerceived && EvaluateBernoulliProbability(m_fProbability);
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
		m_fGroundThreshold = AutoMoDeValue(0.95);
		m_fProbability = FindParameter("p");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::Reset() {}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		AutoMoDeCondition::SetRobotDAO(pc_robot_dao);
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}
}
