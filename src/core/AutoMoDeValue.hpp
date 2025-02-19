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

#include "AutoMoDeObservers.hpp"

namespace argos {
	/**
	 * This class acts as a wrapper to a basic data type. Its utility consists in the automatic
	 * update of the value when it changes. This is implemented through the Observer pattern of
	 * oop, in which this class is an observer entity. The AutoMoDeValue can assume different basic
	 * types, and it will convert the string representation passed by the observable to the correct
	 * one when updating.
	 */
	template <typename T>
	class AutoMoDeValue : public AutoMoDeObserver {
		public:
			/**
			 * Dummy constructor for a useless object.
			 */
			AutoMoDeValue() : AutoMoDeObserver() { };

			/**
			 * Subscription constructor. At creation the object subscribes to the update of the
			 * given parameter. The initial value is not set, and should be set by the observable.
			 * 
			 * @param[in] observable The object managing the FSM values.
			 * @param[in] parameter The name of the parameter that this object is interested in.
			 */
			AutoMoDeValue(AutoMoDeObservable* observable, const std::string parameter) {
				m_Observable = observable;
				m_Parameter = parameter;
				m_Observable->Subscribe(this, m_Parameter);
			}

			/**
			 * Copy constructor. Create a new object that is the copy of the passed one. At
			 * creation, it subscribes to the observable.
			 * 
			 * @param[in] other The object to copy.
			 */
			AutoMoDeValue(const AutoMoDeValue<T>& other) {
				m_Observable = other.m_Observable;
				m_Parameter = other.m_Parameter;
				m_Observable->Subscribe(this, m_Parameter);
			}

			/**
			 * Class destructor. It un-subscribes to the observable.
			 */
			~AutoMoDeValue() {
				m_Observable->Unsubscribe(this, m_Parameter);
			}

			/**
			 * Called when the parameter (event) value change. It parse the value to the desired
			 * data type.
			 * 
			 * @param[in] event The name of the changed parameter.
			 * @param[in] value The new value of the parameter. 
			 */
			virtual void Update(const std::string& event, const std::string& value);

			/**
			 * Copy the value of another object into this. It needs to unsubscribe to previous
			 * parameter and to subscribe the new one, so you need to use it carefully to avoid too
			 * much time waste.
			 * 
			 * @param[in] other The object to copy.
			 * @return The copy of the passed object.
			 */
			AutoMoDeValue<T>& operator = (const AutoMoDeValue<T>& other) {
				// make sure this object is not subscribed anymore to its previous parameter
				if (m_Observable != NULL) {
					m_Observable->Unsubscribe(this, m_Parameter);
				}

				// copy the data and subscribe for the parameter update
				m_Parameter = other.m_Parameter;
				m_Value = other.m_Value;
				m_Observable = other.m_Observable;
				m_Observable->Subscribe(this, m_Parameter);

				return *this;
			}

			/**
			 * The cast operator, converting this object to the desired value type.
			 * 
			 * @return The value casted to the desired type.
			 */
			operator T () const {
				return m_Value;
			}

		private:
			/**
			 * The name of the parameter this object is interested in.
			 */
			std::string m_Parameter;

			/**
			 * The current value of the parameter.
			 */
			T  m_Value;
	};
}

#endif /* AUTOMODE_VALUE_HPP */
