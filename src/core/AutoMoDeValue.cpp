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
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(Real value) {
		m_uDefaultValue.real = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(UInt8 value) {
		m_uDefaultValue.u8 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(UInt16 value) {
		m_uDefaultValue.u16 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(UInt32 value) {
		m_uDefaultValue.u32 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(SInt8 value) {
		m_uDefaultValue.s8 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(SInt16 value) {
		m_uDefaultValue.s16 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(SInt32 value) {
		m_uDefaultValue.s32 = value;
		m_uValue = &m_uDefaultValue;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::AutoMoDeValue(Value* value) {
		m_uValue = value;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeValue::SetPointer(Value* value) {
		m_uValue = value;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator Real () const {
		return m_uValue->real;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt8 () const {
		return m_uValue->u8;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt16 () const {
		return m_uValue->u16;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator UInt32 () const {
		return m_uValue->u32;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt8 () const {
		return m_uValue->s8;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt16 () const {
		return m_uValue->s16;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator SInt32 () const {
		return m_uValue->s32;
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue::operator CColor () const {
		switch (m_uValue->s8) {
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
