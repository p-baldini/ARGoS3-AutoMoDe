/**
 * @file <src/core/AutoMoDeFsmBuilder.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeFsmBuilder.h"

#include <limits>

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::AutoMoDeFsmBuilder() { }

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::~AutoMoDeFsmBuilder() {
		delete cFiniteStateMachine;
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(
		const std::string& str_fsm_config
	) {
		std::istringstream iss(str_fsm_config);
		std::vector<std::string> tokens;
		std::copy(
			std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens)
		);
		return BuildFiniteStateMachine(tokens);
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(
		std::vector<std::string>& vec_fsm_config
	) {
		// create the FSM object to set up and return
		cFiniteStateMachine = new AutoMoDeFiniteStateMachine();

		// try parsing the FSM description
		try {
			auto parameters = new AutoMoDeParameters(vec_fsm_config);
			cFiniteStateMachine->SetParameters(parameters);
		}
		catch (std::exception& e) {
			THROW_ARGOSEXCEPTION("[ERROR] Could not parse the Finite State Machine");
		}

		// get the number of states in the FSM, and create them accordingly
		UInt32 statesCount = cFiniteStateMachine->GetParameters()->GetParameter<UInt32>("nstates");
		for (UInt32 state_id = 0; state_id < statesCount; state_id++) {
			HandleState(state_id);
		}

		return cFiniteStateMachine;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleState(const UInt32 state_id) {
		// create the behavior object to set up
		AutoMoDeBehaviour* newBehavior;

		// get the type of the behavior and instantiate the corresponding class
		UInt8 behaviorType = cFiniteStateMachine->GetParameters()->GetParameter<UInt32>("s", state_id);
		switch (behaviorType) {
			case 0:
				newBehavior = new AutoMoDeBehaviourExploration();
				break;
			case 1:
				newBehavior = new AutoMoDeBehaviourStop();
				break;
			case 2:
				newBehavior = new AutoMoDeBehaviourPhototaxis();
				break;
			case 3:
				newBehavior = new AutoMoDeBehaviourAntiPhototaxis();
				break;
			case 4:
				newBehavior = new AutoMoDeBehaviourAttraction();
				break;
			case 5:
				newBehavior = new AutoMoDeBehaviourRepulsion();
				break;
			case 8:
				newBehavior = new AutoMoDeBehaviourGoToColor();
				break;
			case 9:
				newBehavior = new AutoMoDeBehaviourGoAwayColor();
				break;
			case 10:
				newBehavior = new AutoMoDeBehaviourReactToColor();
				break;
		}

		// set up behavior information and initialize it
		newBehavior->SetIndex(state_id);
		newBehavior->SetIdentifier(behaviorType);
		newBehavior->SetParameters(cFiniteStateMachine->GetParameters());
		newBehavior->Init();

		// add the constructed Behaviour to the FSM
		cFiniteStateMachine->AddBehaviour(newBehavior);

		// get the number of outgoing transition from the state and instantiate them
		UInt8 outgoingTransitions = cFiniteStateMachine->GetParameters()->GetParameter<UInt32>("n", state_id, "0");
		for (UInt8 condition_id = 0; condition_id < outgoingTransitions; condition_id++) {
			HandleTransition(state_id, condition_id);
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleTransition(const UInt32 state_id, const UInt32 condition_id) {
		// create the condition object to set up
		AutoMoDeCondition* newCondition;

		// get the type of the condition and instantiate the corresponding class
		UInt8 conditionType = cFiniteStateMachine->GetParameters()->GetParameter<UInt32>("c", state_id, condition_id);
		switch (conditionType) {
			case 0:
				newCondition = new AutoMoDeConditionBlackFloor();
				break;
			case 1:
				newCondition = new AutoMoDeConditionGrayFloor();
				break;
			case 2:
				newCondition = new AutoMoDeConditionWhiteFloor();
				break;
			case 3:
				newCondition = new AutoMoDeConditionNeighborsCount();
				break;
			case 4:
				newCondition = new AutoMoDeConditionInvertedNeighborsCount();
				break;
			case 5:
				newCondition = new AutoMoDeConditionFixedProbability();
				break;
			case 6:
				newCondition = new AutoMoDeConditionProbColor();
				break;
			case 7:
				newCondition = new AutoMoDeConditionFloorColor();
				break;
		}

		// get the destination state from the FSM description
		UInt8 destinationState = cFiniteStateMachine->GetParameters()->GetParameter<UInt32>("n", state_id, condition_id);

		// TODO: Check here whether unToBehaviour is smaller than the total number of states.

		// the destination state in the FSM ignores the current state; here we want the real index
		// E.G.:
		// 	in FSM: state 1 has a transition to state 0
		//  here: state 1 has a transition to state 0
		// 
		// 	in FSM: state 1 has a transition to state 1
		//  here: state 1 has a transition to state 2
		if (destinationState >= state_id) {
			destinationState += 1;
		}

		// set up condition information and initialize it
		newCondition->SetOriginAndExtremity(state_id, destinationState);
		newCondition->SetIndex(condition_id);
		newCondition->SetIdentifier(conditionType);
		newCondition->SetParameters(cFiniteStateMachine->GetParameters());
		newCondition->Init();

		// add the constructed Condition to the FSM
		cFiniteStateMachine->AddCondition(newCondition);
	}
}
