/**
 * @file <src/modules/AutoMoDeConditionColor.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeConditionProbColor.h"

#include <algorithm>

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionProbColor::AutoMoDeConditionProbColor() {
		m_strLabel = "ProbColor";
		m_fDistance = 6;
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionProbColor::AutoMoDeConditionProbColor(
		AutoMoDeConditionProbColor* pc_condition
	) : AutoMoDeConditionProbColor() {
		m_strLabel = pc_condition->GetLabel();
		m_unIndex = pc_condition->GetIndex();
		m_unIdentifier = pc_condition->GetIndex();
		m_unFromBehaviourIndex = pc_condition->GetOrigin();
		m_unToBehaviourIndex = pc_condition->GetExtremity();
		m_mapParameters = pc_condition->GetParameters();
		m_eTriggerType = pc_condition->m_eTriggerType;
		m_cColorParameter = pc_condition->m_cColorParameter;
		m_fProbability = pc_condition->m_fProbability;
		m_fDistance = pc_condition->m_fDistance;
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionProbColor::Init() {
		m_eTriggerType = FindParameter("t");
		m_cColorParameter = FindParameter("l");
		m_fProbability = FindParameter("p");
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionProbColor* AutoMoDeConditionProbColor::Clone() {
		return new AutoMoDeConditionProbColor(this);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionProbColor::Verify() {
		// get the list of perceived color blobs
		auto colors = m_pcRobotDAO->GetCameraInput().BlobList;

		// filter too near blobs (supposedly own produced color)
		auto isNear = [this](auto o){ return o->Distance < m_fDistance; };
		auto end = std::remove_if(colors.begin(), colors.end(), isNear);
		colors.erase(end, colors.end());

		// create a lambda function to check if a color is of a specific type
		CColor c = GetColorParameter(m_cColorParameter);
		auto isBlobOfColor = [c](auto o){ return o->Color == c; };

		// according to the trigger type consider a different condition and set if it is valid
		bool isValid = false;
		switch (static_cast<TriggerType>((int)m_eTriggerType)) {
			case SPECIFIC_COLOR_DETECTED:
				isValid = std::any_of(colors.begin(), colors.end(), isBlobOfColor);
				break;
			case SPECIFIC_COLOR_UNDETECTED:
				isValid = std::none_of(colors.begin(), colors.end(), isBlobOfColor);
				break;
			case ANY_COLOR_DETECTED:
				isValid = ! colors.empty();
				break;
			case NO_COLOR_DETECTED:
				isValid = colors.empty();
				break;
		}

		return isValid && EvaluateBernoulliProbability(m_fProbability);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionProbColor::Reset() {
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionProbColor::Adapt(Real reward) {
		m_fProbability.Adapt(reward);
	}
}
