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

	AutoMoDeConditionFixedProbability::AutoMoDeConditionFixedProbability(AutoMoDeConditionFixedProbability* pc_condition) {
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

	AutoMoDeConditionFixedProbability* AutoMoDeConditionFixedProbability::Clone() {
		return new AutoMoDeConditionFixedProbability(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFixedProbability::Init() {
		m_fProbability.Init(FindParameter<Real>("p"));
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

	/****************************************/
	/****************************************/

	void AutoMoDeConditionFixedProbability::Adapt(Real reward) {
		m_fProbability.Adapt(reward);
	}
 }
