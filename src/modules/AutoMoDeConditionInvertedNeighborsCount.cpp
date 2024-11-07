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

	AutoMoDeConditionInvertedNeighborsCount::AutoMoDeConditionInvertedNeighborsCount(AutoMoDeConditionInvertedNeighborsCount* pc_condition) {
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

	AutoMoDeConditionInvertedNeighborsCount* AutoMoDeConditionInvertedNeighborsCount::Clone() {
		return new AutoMoDeConditionInvertedNeighborsCount(this);
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
		m_fParameterEta.Init(FindParameter<Real>("w"));
		m_unParameterXi.Init(FindParameter<UInt8>("p"));
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionInvertedNeighborsCount::Adapt(Real reward) {
		m_fParameterEta.Adapt(reward);
		m_unParameterXi.Adapt(reward);
	}
}
