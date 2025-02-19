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

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

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

	AutoMoDeConditionBlackFloor::AutoMoDeConditionBlackFloor(
		AutoMoDeConditionBlackFloor* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionBlackFloor::Init() {
		m_fGroundThreshold = 0.1;
		m_fProbability = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionBlackFloor* AutoMoDeConditionBlackFloor::Clone() {
		return new AutoMoDeConditionBlackFloor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionBlackFloor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "p=" << m_fProbability << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionBlackFloor::Verify() {
		// according to the robot capabilities, verify if the ground is black
		bool blackPerceived = m_bBasicPerceptionCapabilities
			? m_pcRobotDAO->GetGroundInput().Center <= (Real) m_fGroundThreshold
			: m_pcRobotDAO->GetGroundReading() <= (Real) m_fGroundThreshold;

		// if the ground is black, the transition depends on the sampled value
		return blackPerceived && EvaluateBernoulliProbability(m_fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionBlackFloor::Reset() {
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionBlackFloor::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		AutoMoDeCondition::SetRobotDAO(pc_robot_dao);
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}
}
