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
	) : AutoMoDeCondition(pc_condition) {
		m_fDistance = pc_condition->m_fDistance;
		Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionProbColor::Init() {
		m_eTriggerType = m_Parameters->GetParameter<UInt8>("t", m_unFromBehaviourIndex, m_unIndex);
		m_cColorParameter = m_Parameters->GetParameter<CColor>("l", m_unFromBehaviourIndex, m_unIndex);
		m_fProbability = m_Parameters->GetParameter<Real>("p", m_unFromBehaviourIndex, m_unIndex);
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionProbColor* AutoMoDeConditionProbColor::Clone() {
		return new AutoMoDeConditionProbColor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeConditionProbColor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "t=" << m_eTriggerType << std::endl;
		ss << "l=" << m_cColorParameter << std::endl;
		ss << "p=" << m_fProbability << std::endl;
		return ss.str();
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
		auto isBlobOfColor = [this](auto o){ return o->Color == (CColor) m_cColorParameter; };

		// according to the trigger type consider a different condition and set if it is valid
		bool isValid = false;
		switch (static_cast<TriggerType>((UInt8) m_eTriggerType)) {
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
}
