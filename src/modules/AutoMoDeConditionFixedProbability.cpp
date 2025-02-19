/**
 * @file <src/modules/AutoMoDeConditionFixedProbability.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionFixedProbability.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionFixedProbability::AutoMoDeConditionFixedProbability() {
		m_strLabel = "FixedProbability";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionFixedProbability::~AutoMoDeConditionFixedProbability() {}

	/****************************************/
	/****************************************/

	AutoMoDeConditionFixedProbability::AutoMoDeConditionFixedProbability(
		AutoMoDeConditionFixedProbability* pc_condition
	) : AutoMoDeCondition(pc_condition) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionFixedProbability* AutoMoDeConditionFixedProbability::Clone() {
		return new AutoMoDeConditionFixedProbability(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionFixedProbability::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "p=" << m_fProbability << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFixedProbability::Init() {
		m_fProbability = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionFixedProbability::Verify() {
		return EvaluateBernoulliProbability(m_fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFixedProbability::Reset() {
		Init();
	}
}
