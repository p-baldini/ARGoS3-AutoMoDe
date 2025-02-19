#ifndef AUTOMODE_PARAMETERS_HPP
#define AUTOMODE_PARAMETERS_HPP

#include "AutoMoDeAdapter.hpp"
#include "AutoMoDeObservers.hpp"
#include "AutoMoDeValue.hpp"

#include <argos3/core/utility/logging/argos_log.h>
#include <map>

namespace argos {
	class AutoMoDeParameters : public AutoMoDeObservable, public AutoMoDeAdapter {
		public:
			/**
			 * Given a string-represented FSM, extract all its parameters.
			 * 
			 * @param[in] fsm The string-represented FSM.
			 */
			AutoMoDeParameters(const std::string& fsm);

			/**
			 * Given a FSM represented as a sequence of tokens (i.e., strings), extract all its
			 * parameters.
			 * 
			 * @param[in] fsm_tokens The FSM represented as a sequence of tokens.
			 */
			AutoMoDeParameters(const std::vector<std::string>& fsm_tokens);

			/**
			 * Copy constructor. Copy the parameters contained in the other object, but NOT its
			 * registered observers.
			 * 
			 * @param[in] other The object to copy.
			 */
			AutoMoDeParameters(const AutoMoDeParameters& other);

			/**
			 * Checks whether the parameter with the given name exists.
			 * 
			 * @param[in] name The name of the parameter to check for existance.
			 */
			bool HasParameter(const std::string name);

			/**
			 * Get the value of a parameter with the given name. The value is encapsuled in a class
			 * allowing the automatic update of its value whether should it be dynamic.
			 * This function even allows setting a default value in case the parameter does not
			 * exists. In this case, the parameter and its default value are registered and then
			 * returned to the caller.
			 * 
			 * @param[in] name The name of the parameter that we want.
			 * @param[in] default_value Optional value to use if the parameter is unknown.
			 * @return The wrapped and always-updated value of the parameter.
			 */
			template <typename T>
			AutoMoDeValue<T> GetParameter(
				const std::string name,
				const std::string default_value=""
			) {
				if (! HasParameter(name) && ! default_value.empty()) {
					m_ParsedValues[name].push_back(default_value);
				}
				return AutoMoDeValue<T>(this, name);
			}

			/**
			 * Get the value of a parameter with the given name of the given behavior. The value is
			 * encapsuled in a class allowing the automatic update of its value whether should it
			 * be dynamic.
			 * This function even allows setting a default value in case the parameter does not
			 * exists. In this case, the parameter and its default value are registered and then
			 * returned to the caller.
			 * 
			 * @param[in] name The name of the parameter that we want.
			 * @param[in] behavior_id The id of the behavior the parameter belongs to.
			 * @param[in] default_value Optional value to use if the parameter is unknown.
			 * @return The wrapped and always-updated value of the parameter.
			 */
			template <typename T>
			AutoMoDeValue<T> GetParameter(
				const std::string name,
				UInt32 behavior_id,
				const std::string default_value=""
			) {
				std::ostringstream oss;
				oss << name << behavior_id;
				return GetParameter<T>(oss.str(), default_value);
			}

			/**
			 * Get the value of a parameter with the given name of the given transition. The value
			 * is encapsuled in a class allowing the automatic update of its value whether should it
			 * be dynamic.
			 * This function even allows setting a default value in case the parameter does not
			 * exists. In this case, the parameter and its default value are registered and then
			 * returned to the caller.
			 * 
			 * @param[in] name The name of the parameter that we want.
			 * @param[in] behavior_id The id of the behavior the transition starts from.
			 * @param[in] condition_id The id of the condition the parameter belongs to.
			 * @param[in] default_value Optional value to use if the parameter is unknown.
			 * @return The wrapped and always-updated value of the parameter.
			 */
			template <typename T>
			AutoMoDeValue<T> GetParameter(
				const std::string name,
				UInt32 behavior_id,
				UInt32 condition_id,
				const std::string default_value=""
			) {
				std::ostringstream oss;
				oss << name << behavior_id << "x" << condition_id;
				return GetParameter<T>(oss.str(), default_value);
			}

			/**
			 * Override of the `AutoMoDeObservable` method. Beside subscribing the observer, it also
			 * immediately updates its value.
			 * 
			 * @param[in] observer The object to be notified when the event fires.
			 * @param[in] event The event that the observer is interested in.
			 */
			void Subscribe(AutoMoDeObserver* observer, const std::string event) override;

			/**
			 * @see AutoMoDeAdapter::SetValues
			 */
			virtual void SetValues(UInt32 arm_index) override;

		private:
			/**
			 * Contains for each parsed parameter its possible values.
			 */
			std::map<std::string, std::vector<std::string>> m_ParsedValues;

			/**
			 * Contains all the possible combinations of dynamic parameter values. E.g.:
			 *  [
			 *      ('a'=1, 'b'=2),  # combination 1
			 *      ('a'=1, 'b'=3),  # combination 2
			 *      ('a'=8, 'b'=2),  # combination 3
			 *      ('a'=8, 'b'=3)   # combination 4
			 *  ]
			 */
			std::vector<std::map<std::string, std::string>> m_Configurations;

			/**
			 * The index of the currently used configuration in `m_Configurations'.
			 */
			UInt32 m_ConfigurationIndex;

			/**
			 * Parse the FSM parameters and set up the class.
			 * 
			 * @param[in] fsm_tokens The sequence of strings defining the FSM.
			 */
			void ParseFSMParameters(const std::vector<std::string>& fsm_tokens);

			/**
			 * Search the value of the required parameter. It allows selecting the active value of
			 * a dynamic parameter.
			 * 
			 * @param[in] name The name of the parameter value to retrieve.
			 */
			std::string GetValue(const std::string name);

			/**
			 * Disable access to equal operator.
			 */
			AutoMoDeParameters& operator = (const AutoMoDeParameters& other) { return *this; };
	};
}

#endif /* AUTOMODE_PARAMETERS_HPP */
