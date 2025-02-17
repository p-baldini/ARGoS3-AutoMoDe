/**
 * @file <src/core/AutoMoDeAdapter.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_ADAPTER_HPP
#define AUTOMODE_ADAPTER_HPP

#include "AutoMoDeValue.hpp"

#include <argos3/core/simulator/simulator.h>
#include <list>

namespace argos {
	/**
	 * The object of the FSM that manages the selection of dynamic values.
	 */
	class AutoMoDeAdapter {
		public:
			/**
			 * Empty constructor. Initialize the object variables.
			 */
			AutoMoDeAdapter();

			/**
			 * Copy constructor. Creates a copy of the passed adapter.
			 */
			AutoMoDeAdapter(const AutoMoDeAdapter& other);

			/**
			 * Add a new adaptable parameter with its possible values, and return the adaptable
			 * object that allows a flawless access to the currently selected value.
			 * 
			 * @param[in] values The set of possible values the parameter can assume.
			 * @return The class that allows accessing the value currently in use for this
			 * parameter.
			 */
			AutoMoDeValue AddParameter(std::vector<Real> values);

			/**
			 * Decide which combination of parameter values to use according to the performance of
			 * the last. This method is based on a multi-armed banding algorithm.
			 * 
			 * @param[in] reward The performance of the last tested set of values.
			 */
			void Adapt(Real reward);

			/**
			 * Set the evaluation time of each combination of parameter values.
			 * 
			 * @param[in] evaluationTime The number of steps a set of values will be evaluated for.
			 */
			void SetEvaluationTime(UInt32 evaluationTime);

			/**
			 * Returns the evaluation time of a combination of parameter values when adapting.
			 * 
			 * @return The time a combination of parameter values will be tested for.
			 */
			UInt32 GetEvaluationTime() const;

		private:
			/**
			 * The number of steps after which the parameter should adapt.
			 */
			UInt32 m_uEvaluationTime;

			/**
			 * The current evaluation step, since the start of the evaluation.
			 */
			UInt32 m_uElapsedTime;

			/**
			 * The index of the combination of parameter values currently in use.
			 */
			UInt32 m_uArmIndex;

			/**
			 * The set of all the possible parameter combinations.
			 */
			std::vector<std::vector<Real>> m_vParameterCombinations;

			/**
			 * Contains the cumulative reward of each parameter-value combination.
			 */
			std::vector<Real> m_fRewards;

			/**
			 * Contains the number of times a parameter-value combination has been tried for.
			 */
			std::vector<SInt32> m_iPulls;

			/**
			 * The current / active value of each parameter.
			 */
			std::list<Real> m_vActiveParameterValues;

			/**
			 * The value of each static parameter.
			 */
			std::list<Real> m_vStaticParameterValues;

			/**
			 * Select an arm to use according to the number of trials and performance.
			 * 
			 * @return The index of the arm to use.
			 */
			UInt32 SelectArm();

			/**
			 * Sets the values conbination to use according to the selected arm.
			 */
			void SetValues();
	};
}

#endif /* AUTOMODE_ADAPTER_HPP */
