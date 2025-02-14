/**
 * @file <src/modules/AutoMoDeCondition.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeCondition.h"

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

namespace argos {

	/****************************************/
	/****************************************/

	const std::string AutoMoDeCondition::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel;
		for (auto& it : m_mapParameters) {
			ss << "\\n" << it.first << "=" << (Real) it.second;
		}
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::AddParameter(
		const std::string& str_identifier, const AutoMoDeValue& f_value
	) {
		m_mapParameters.insert(
			std::pair<std::string, AutoMoDeValue>(str_identifier, f_value)
		);
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeCondition::GetOrigin() const {
		return m_unFromBehaviourIndex;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeCondition::GetExtremity() const {
		return m_unToBehaviourIndex;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetOrigin(const UInt32& un_from) {
		m_unFromBehaviourIndex = un_from;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetExtremity(const UInt32& un_to) {
		m_unToBehaviourIndex = un_to;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetOriginAndExtremity(const UInt32& un_from, const UInt32& un_to) {
		m_unFromBehaviourIndex = un_from;
		m_unToBehaviourIndex = un_to;
	}

	/****************************************/
	/****************************************/

	const std::string& AutoMoDeCondition::GetLabel() const {
		return m_strLabel;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetIndex(const UInt32& un_index) {
		m_unIndex = un_index;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeCondition::GetIndex() const {
		return m_unIndex;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetIdentifier(const UInt32& un_id) {
		m_unIdentifier = un_id;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeCondition::GetIdentifier() const {
		return m_unIdentifier;
	}

	/****************************************/
	/****************************************/

	const std::map<std::string, AutoMoDeValue> AutoMoDeCondition::GetParameters() const {
		return m_mapParameters;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeCondition::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		m_pcRobotDAO = pc_robot_dao;
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeCondition::EvaluateBernoulliProbability(const Real& f_probability) const {
		return m_pcRobotDAO->GetRandomNumberGenerator()->Bernoulli(f_probability);
	}

	/****************************************/
	/****************************************/

	// Return the color parameter
	CColor AutoMoDeCondition::GetColorParameter(const UInt32& un_value) {
		CColor cColorParameter;
		switch(un_value){
		case 0:
			cColorParameter = CColor::BLACK;
			break;
		case 1:
			cColorParameter = CColor::GREEN;
			break;
		case 2:
			cColorParameter = CColor::BLUE;
			break;
		case 3:
			cColorParameter = CColor::RED;
			break;
		case 4:
			cColorParameter = CColor::YELLOW;
			break;
		case 5:
			cColorParameter = CColor::MAGENTA;
			break;
		case 6:
			cColorParameter = CColor::CYAN;
			break;
		default:
			cColorParameter = CColor::BLACK;
		}
		return cColorParameter;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue AutoMoDeCondition::FindParameter(const char tag[]) {
		auto it = m_mapParameters.find(tag);
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter '" << tag
					<< "' for condition: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		return it->second;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue AutoMoDeCondition::FindParameter(const char tag[], AutoMoDeValue defaultValue) {
		if (HasParameter(tag)) {
			return FindParameter(tag);
		}
		return defaultValue;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeCondition::HasParameter(const char tag[]) {
		auto it = m_mapParameters.find(tag);
		return it != m_mapParameters.end();
	}
}
