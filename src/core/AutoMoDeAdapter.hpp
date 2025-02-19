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
	 * This class manages the selection of values according to a multi-armed bandit algorithm.
	 * Currently, it completely abstracts away the type of data, only working with indexes.
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
			 * Decide which 'arm' to use according to the performance of the last and the time
			 * instant.
			 * 
			 * @param[in] reward The performance of the last tested arm.
			 */
			void Adapt(Real reward);

			/**
			 * Set the number of arms available. Calling this method will delete any other data
			 * previously contained.
			 * 
			 * @param[in] arms_count The number of arms to try.
			 */
			void SetArmsCount(UInt32 arms_count);

			/**
			 * Set the evaluation time of each arm.
			 * 
			 * @param[in] evaluationTime The number of steps an arm will be evaluated for.
			 */
			void SetEvaluationTime(UInt32 evaluationTime);

			/**
			 * Set the value of the arm. Must be implemented by derived classes.
			 * 
			 * @param[in] arm_index The index of the arm to set.
			 */
			virtual void SetValues(UInt32 arm_index) = 0;

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
			 * Contains the cumulative reward of each parameter-value combination.
			 */
			std::vector<Real> m_fRewards;

			/**
			 * Contains the number of times a parameter-value combination has been tried for.
			 */
			std::vector<UInt32> m_iPulls;

			/**
			 * Select an arm to use according to the number of trials and performance.
			 * 
			 * @return The index of the arm to use.
			 */
			UInt32 SelectArm();

			/**
			 * Disable access to equal operator.
			 */
			AutoMoDeAdapter& operator = (const AutoMoDeAdapter& other) { return *this; };
	};
}

#endif /* AUTOMODE_ADAPTER_HPP */
