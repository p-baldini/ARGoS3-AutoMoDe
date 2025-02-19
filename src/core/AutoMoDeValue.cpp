/**
 * @file <src/core/AutoMoDeValue.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeValue.hpp"

#include <argos3/core/utility/datatypes/color.h>

namespace argos {

	/****************************************/
	/****************************************/

	template <>
	void AutoMoDeValue<std::string>::Update(const std::string& event, const std::string& value) {
		m_Value = value;
	}

	template <>
		void AutoMoDeValue<Real>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtod(value.c_str(), NULL);
	}

	template <>
	void AutoMoDeValue<UInt8>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtoul(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<UInt16>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtoul(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<UInt32>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtoul(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<SInt8>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtol(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<SInt16>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtol(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<SInt32>::Update(const std::string& event, const std::string& value) {
		m_Value = std::strtol(value.c_str(), NULL, 10);
	}

	template <>
	void AutoMoDeValue<CColor>::Update(const std::string& event, const std::string& value) {
		switch (std::strtoul(value.c_str(), NULL, 10)) {
			case 0:
				m_Value = CColor::BLACK;
				break;
			case 1:
				m_Value = CColor::GREEN;
				break;
			case 2:
				m_Value = CColor::BLUE;
				break;
			case 3:
				m_Value = CColor::RED;
				break;
			case 4:
				m_Value = CColor(250,80,0);
				break;
			case 5:
				m_Value = CColor(150,0,60);
				break;
			case 6:
				m_Value = CColor(0,200,50);
				break;
			default:
				m_Value = CColor::BLACK;
		}
	}
}
