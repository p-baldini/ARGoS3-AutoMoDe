/**
 * @file <src/core/AutoMoDeValue.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_VALUE_HPP
#define AUTOMODE_VALUE_HPP

#include <argos3/core/utility/datatypes/color.h>

namespace argos {
	/**
	 * This class acts as a wrapper to a basic data type. Its utility consists in the smooth
	 * access to a value managed by an external class, without the need for a direct referencing.
	 */
	class AutoMoDeValue {
		public:
			/**
			 * The variable containing the value information. The correct type is inferred by the
			 * context.
			 */
			union Value {
				Real   real;
				UInt8  u8;
				UInt16 u16;
				UInt32 u32;
				SInt8  s8;
				SInt16 s16;
				SInt32 s32;
			};

			/**
			 * Empty class constructor. It uses a default value of 0.
			 */
			AutoMoDeValue();

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(Real value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(UInt8 value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(UInt16 value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(UInt32 value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(SInt8 value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(SInt16 value);

			/**
			 * Static value constructor. Asking for the value will always return the specified one.
			 * 
			 * @param[in] value The fixed value of the parameter.
			 */
			AutoMoDeValue(SInt32 value);

			/**
			 * Dynamic value constructor. Asking for the value possibly returns a different value
			 * each time.
			 * 
			 * @param[in] value The pointer to the variable containing the value of the parameter.
			 */
			AutoMoDeValue(Value* value);

			/**
			 * Dynamic value setter. Asking for the value possibly returns a different value
			 * each time.
			 * 
			 * @param[in] value The pointer to the variable containing the value of the parameter.
			 */
			void SetPointer(Value* value);

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator Real () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator UInt8 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator UInt16 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator UInt32 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator SInt8 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator SInt16 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator SInt32 () const;

			/**
			 * The cast operator, converting the value wrapped by this class to the desired one.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator CColor () const;

		private:
			/**
			 * The pointer to the variable containing the value of the parameter.
			 */
			Value* m_uValue;

			/**
			 * The default and fixed value of the parameter.
			 */
			Value  m_uDefaultValue;
	};
}

#endif /* AUTOMODE_VALUE_HPP */
