/**
 * @file <src/modules/AutoMoDeConditionFloorColor.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionFloorColor.hpp"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionFloorColor::AutoMoDeConditionFloorColor() {
		m_strLabel = "FloorColor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionFloorColor::AutoMoDeConditionFloorColor(
		AutoMoDeConditionFloorColor* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionFloorColor* AutoMoDeConditionFloorColor::Clone() {
		return new AutoMoDeConditionFloorColor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionFloorColor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "t=" << m_eType << std::endl;
		ss << "v=" << m_fGroundColor << std::endl;
		ss << "p=" << m_fProbability << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionFloorColor::Verify() {
		Real reading = m_bBasicPerceptionCapabilities
			? m_pcRobotDAO->GetGroundInput().Center
			: m_pcRobotDAO->GetGroundReading();

		// check if the robot perceives a value in the surrounding of the desired value
		bool perceived = (Real) m_fGroundColor - .25 <= reading && reading <= (Real) m_fGroundColor + .25;

		// if the condition type is `absence`, negate the presence of the perceived color
		perceived = (UInt8) m_eType == 1 ? ! perceived : perceived;

		// if the ground condition is enabled, check if transition probability
		return perceived && EvaluateBernoulliProbability(m_fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFloorColor::Reset() {
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFloorColor::Init() {
		m_eType = m_Parameters->GetParameter<UInt8>("t", m_unFromBehaviourIndex, m_unIndex);
		m_fGroundColor = m_Parameters->GetParameter<Real>("v", m_unFromBehaviourIndex, m_unIndex);
		m_fProbability = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}
}
