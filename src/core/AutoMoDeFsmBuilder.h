/**
 * @file <src/core/AutoMoDeFsmBuilder.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 * 
 * @brief This class is used to parse the configuration of
 * 				the stochastic finite state machine and instanciate the
 * 				different modules (behaviours and conditions). These modules
 * 				are added to the AutoMoDeFiniStateMachine created.
 */
#ifndef AUTOMODE_FSM_BUILDER_H
#define AUTOMODE_FSM_BUILDER_H

#include "AutoMoDeFiniteStateMachine.h"
#include "AutoMoDeParameters.hpp"

#include <argos3/core/utility/logging/argos_log.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdlib.h>

namespace argos {
	class AutoMoDeFsmBuilder {
		public:
			/**
			 * Dummy class constructor.
			 */
			AutoMoDeFsmBuilder();

			/**
			 * Class destructor. Frees the memory occupied by the FSM object.
			 */
			virtual ~AutoMoDeFsmBuilder();

			/**
			 * Creates an AutoMoDeFiniteStateMachine based on a configuration as a vector of
			 * strings. This method should be called when the FSM is created from the
			 * AutoMoDeMain.cpp.
			 * 
			 * @param[in] str_fsm_config The sequence of tokens describing the FSM.
			 * @return The built FSM.
			 */
			AutoMoDeFiniteStateMachine* BuildFiniteStateMachine(
				std::vector<std::string>& vec_fsm_config
			);

			/**
			 * Creates an AutoMoDeFiniteStateMachine based on a configuration as a string.
			 * This method should be called when the FSM is created from the
			 * AutoMoDeController.cpp.
			 * 
			 * @param[in] str_fsm_config The string-representation of the FSM.
			 * @return The built FSM.
			 */
			AutoMoDeFiniteStateMachine* BuildFiniteStateMachine(
				const std::string& str_fsm_config
			);

		private:
			/**
			 * Creates a AutoMoDeBehaviour from a state configuration and add it to the
			 * AutoMoDeFiniStateMachine in construction.
			 * Strips the different transitions and calls HandleTransition for their creation.
			 * 
			 * @param[in] state_id The ID of the behavior.
			 */
			void HandleState(const UInt32 state_id);

			/**
			 * Creates a AutoMoDeCondition from a transition configuration and add it to the
			 * AutoMoDeFiniStateMachine under construction.
			 * 
			 * @param[in] state_id The ID of the origin behavior of the transition.
			 * @param[in] condition_id The ID of the transition.
			 */
			void HandleTransition(const UInt32 state_id, const UInt32 condition_id);

			/**
			 * Pointer to the FSM under construction.
			 */
			AutoMoDeFiniteStateMachine* cFiniteStateMachine;
	};
}

#endif /* AUTOMODE_FSM_BUILDER_H */
