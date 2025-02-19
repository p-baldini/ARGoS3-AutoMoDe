/**
 * @file <src/modules/AutoMoDeConditionNeighborsCount.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionNeighborsCount.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionNeighborsCount::AutoMoDeConditionNeighborsCount() {
		m_strLabel = "NeighborsCount";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionNeighborsCount::~AutoMoDeConditionNeighborsCount() {}

	/****************************************/
	/****************************************/

	AutoMoDeConditionNeighborsCount::AutoMoDeConditionNeighborsCount(
		AutoMoDeConditionNeighborsCount* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionNeighborsCount* AutoMoDeConditionNeighborsCount::Clone() {
		return new AutoMoDeConditionNeighborsCount(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionNeighborsCount::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "w=" << m_fParameterEta << std::endl;
		ss << "p=" << m_unParameterXi << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionNeighborsCount::Verify() {
		UInt32 unNumberNeighbors = m_pcRobotDAO->GetNumberNeighbors();
		Real fProbability = (1/(1 + exp(m_fParameterEta * ((int)m_unParameterXi - (int)unNumberNeighbors))));
		return EvaluateBernoulliProbability(fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionNeighborsCount::Reset() {

	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionNeighborsCount::Init() {
		m_fParameterEta = m_Parameters->GetParameter<Real>("w", m_unFromBehaviourIndex, m_unIndex);
		m_unParameterXi = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionNeighborsCount::Adapt(Real reward) {}
}
