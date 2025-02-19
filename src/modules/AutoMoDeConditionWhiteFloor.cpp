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

	AutoMoDeConditionWhiteFloor::AutoMoDeConditionWhiteFloor(
		AutoMoDeConditionWhiteFloor* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionWhiteFloor* AutoMoDeConditionWhiteFloor::Clone() {
		return new AutoMoDeConditionWhiteFloor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionWhiteFloor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "p=" << m_fProbability << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionWhiteFloor::Init() {
		m_fGroundThreshold = 0.95;
		m_fProbability = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
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
