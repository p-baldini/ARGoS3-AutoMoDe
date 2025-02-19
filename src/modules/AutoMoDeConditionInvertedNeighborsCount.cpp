/**
 * @file <src/modules/AutoMoDeConditionInvertedNeighborsCount.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionInvertedNeighborsCount.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionInvertedNeighborsCount::AutoMoDeConditionInvertedNeighborsCount() {
		m_strLabel = "InvertedNeighborsCount";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionInvertedNeighborsCount::~AutoMoDeConditionInvertedNeighborsCount() {}

	/****************************************/
	/****************************************/

	AutoMoDeConditionInvertedNeighborsCount::AutoMoDeConditionInvertedNeighborsCount(
		AutoMoDeConditionInvertedNeighborsCount* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionInvertedNeighborsCount* AutoMoDeConditionInvertedNeighborsCount::Clone() {
		return new AutoMoDeConditionInvertedNeighborsCount(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionInvertedNeighborsCount::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "w=" << m_fParameterEta << std::endl;
		ss << "p=" << m_unParameterXi << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionInvertedNeighborsCount::Verify() {
		UInt32 unNumberNeighbors = m_pcRobotDAO->GetNumberNeighbors();
		Real fProbability = 1 - (1/(1 + exp(m_fParameterEta * ((int)m_unParameterXi - (int)unNumberNeighbors))));
		return EvaluateBernoulliProbability(fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionInvertedNeighborsCount::Reset() {

	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionInvertedNeighborsCount::Init() {
		m_fParameterEta = m_Parameters->GetParameter<Real>("w", m_unFromBehaviourIndex, m_unIndex);
		m_unParameterXi = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionInvertedNeighborsCount::Adapt(Real reward) {}
}
