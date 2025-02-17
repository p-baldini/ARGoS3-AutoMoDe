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

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue() {
		m_uDefaultValue = { };
		m_rValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(Real value) : AutoMoDeValue() {
		m_uDefaultValue = value;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(Real* value) : AutoMoDeValue() {
		m_rValue = value;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(const AutoMoDeValue& other) : AutoMoDeValue() {
		// if the pointer is dummy, copy the default value and ignore the pointer
		if (other.m_rValue == &other.m_uDefaultValue) {
			m_uDefaultValue = other.m_uDefaultValue;
		}
		// if the pointer is meaningful, copy it in the new object
		else {
			m_rValue = other.m_rValue;
		}
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue& AutoMoDeValue::operator = (const AutoMoDeValue& other) {
		// if the pointer is dummy, copy the default value and ignore the pointer
		if (other.m_rValue == &other.m_uDefaultValue) {
			m_uDefaultValue = other.m_uDefaultValue;
			m_rValue = &m_uDefaultValue;
		}
		// if the pointer is meaningful, copy it in the new object
		else {
			m_uDefaultValue = { };
			m_rValue = other.m_rValue;
		}
		return *this;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator Real () const {
		return *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt8 () const {
		return (UInt8) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt16 () const {
		return (UInt16) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt32 () const {
		return (UInt32) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt8 () const {
		return (SInt8) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt16 () const {
		return (SInt16) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt32 () const {
		return (SInt32) *m_rValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator CColor () const {
		switch ((SInt8) *m_rValue) {
			case 0:
				return CColor::BLACK;
			case 1:
				return CColor::GREEN;
			case 2:
				return CColor::BLUE;
			case 3:
				return CColor::RED;
			case 4:
				return CColor(250,80,0);
			case 5:
				return CColor(150,0,60);
			case 6:
				return CColor(0,200,50);
		}
		return CColor::BLACK;
	}
}
