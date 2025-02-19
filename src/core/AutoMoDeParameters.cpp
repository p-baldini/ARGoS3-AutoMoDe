#include "AutoMoDeParameters.hpp"

#include <iterator>

namespace argos {

	/****************************************/
	/****************************************/

	/**
	 * Checks if a string represents a parameter (instead, for instance, a value).
	 * 
	 * @param[in] name The string possibly indicating a parameter.
	 * @return True if the string indicates a parameter, False otherwise.
	 */
	bool IsParameter(const std::string name) {
		return name.rfind("--", 0) == 0;
	};

	/****************************************/
	/****************************************/

	/**
	 * Checks if a string represents a value (instead, for instance, a parameter).
	 * 
	 * @param[in] name The string possibly representing a value.
	 * @return True if the string represents a value, False otherwise.
	 */
	bool IsValue(const std::string name) {
		return ! IsParameter(name);
	};

	/****************************************/
	/****************************************/

	/**
	 * Extract the name of a parameter.
	 * 
	 * @param[in] name The string containing the parameter name.
	 * @return The name of the parameter.
	 */
	std::string GetName(const std::string name) {
		return name.substr(2);
	};

	/****************************************/
	/****************************************/

	AutoMoDeParameters::AutoMoDeParameters(const std::string& fsm) {
		// split the string into tokens separated by spaces
		std::istringstream iss(fsm);
		std::vector<std::string> fsm_tokens;
		std::copy(
			std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(fsm_tokens)
		);
		ParseFSMParameters(fsm_tokens);
	}

	/****************************************/
	/****************************************/

	AutoMoDeParameters::AutoMoDeParameters(const std::vector<std::string>& fsm_tokens) {
		ParseFSMParameters(fsm_tokens);
	};

	/****************************************/
	/****************************************/

	AutoMoDeParameters::AutoMoDeParameters(
		const AutoMoDeParameters& other
	) : AutoMoDeAdapter(other) {
		// copy all the registered parameters
		for (const auto& [k, v] : other.m_ParsedValues) {
			m_ParsedValues[k] = std::vector<std::string>(v);
		}

		// copy all the possible parameter-value configurations
		for (const auto& m : other.m_Configurations) {
			std::map<std::string, std::string> map;

			for (const auto& [k, v] : m) {
				map[k] = v;
			}

			m_Configurations.push_back(map);
		}

		m_ConfigurationIndex = other.m_ConfigurationIndex;
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeParameters::HasParameter(const std::string name) {
		return m_ParsedValues.find(name) != m_ParsedValues.end();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeParameters::Subscribe(AutoMoDeObserver* observer, const std::string event) {
		AutoMoDeObservable::Subscribe(observer, event);
		observer->Update(event, GetValue(event));
	}

	/****************************************/
	/****************************************/

	void AutoMoDeParameters::SetValues(UInt32 arm_index) {
		for (const auto& [k, v] : m_Configurations[arm_index]) {
			for (auto& o : m_Observers[k]) {
				o->Update(k, v);
			}
		}
		m_ConfigurationIndex = arm_index;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeParameters::ParseFSMParameters(const std::vector<std::string>& fsm_tokens) {
		// parse tokens into parameters and values
		std::string current_parameter;
		for (std::string token : fsm_tokens) {
			// if the token is a parameter name, the following data could be its value(s): save it
			if (IsParameter(token)) {
				current_parameter = GetName(token);
			}

			// if the token is a value, add it to the list of the previously encountered parameter
			if (IsValue(token)) {
				m_ParsedValues[current_parameter].push_back(token);
			}
		}

		// create the enumeration of all the possible parameter-values configuration
		// ignoring static values (they remain the same through all the simualtion)
		for (const auto& [name, collection] : m_ParsedValues) {
			if (collection.size() <= 1) {
				continue;
			}

			// save the old number of configurations and calculate the new one
			UInt32 old_configurations_count = m_Configurations.size();
			UInt32 new_configurations_count = old_configurations_count == 0
				? collection.size()
				: collection.size() * old_configurations_count;

			// resize the configuration vector to contain the new combinations
			m_Configurations.resize(new_configurations_count);

			// the total number of configurations multiplies with the number of new values
			// copy the previous configuration to subsequently add the new values to each
			for (UInt32 i = 0; i < new_configurations_count; i++) {
				if (old_configurations_count > 0) {
					m_Configurations[i] = m_Configurations[i % old_configurations_count];
				}
			}

			// append each value in collection to one of the configurations
			for (UInt32 i = 0; i < new_configurations_count; i++) {
				if (old_configurations_count == 0) {
					m_Configurations[i][name] = collection[i];
				}
				else {
					m_Configurations[i][name] = collection[i / old_configurations_count];
				}
			}
		}

		// set number of configuration and the starting configuration index to zero
		SetArmsCount(m_Configurations.size());
		m_ConfigurationIndex = 0;
	}

	/****************************************/
	/****************************************/

	std::string AutoMoDeParameters::GetValue(const std::string name) {
		// search the parameter among the parsed ones
		auto it1 = m_ParsedValues.find(name);

		// if the parameter does not exists or does not have a value, launch and exception
		if (it1 == m_ParsedValues.end() || it1->second.size() == 0) {
			LOGERR << "[FATAL] Missing parameter '" << name << "'" << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}

		// if the parameter is static, return a defaulted AutoMoDeValue
		if (it1->second.size() == 1) {
			return it1->second[0];
		}

		// the parameter is dynamic: get its value-pointer
		auto it2 = m_Configurations[m_ConfigurationIndex].find(name);
		return it2->second;
	}
}
