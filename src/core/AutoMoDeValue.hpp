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
	 * As the AutoMoDe FSM parser converts string-values into doubles, all the data will be stored
	 * in that format and converted at need to the desired type.
	 */
	class AutoMoDeValue {
		public:
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
			 * Dynamic value constructor. Asking for the value possibly returns a different value
			 * each time.
			 * 
			 * @param[in] value The pointer to the variable containing the value of the parameter.
			 */
			AutoMoDeValue(Real* value);

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
			Real* m_rValue;

			/**
			 * The default and fixed value of the parameter.
			 */
			Real  m_uDefaultValue;
	};
}

#endif /* AUTOMODE_VALUE_HPP */
