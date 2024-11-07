/**
 * @file <src/modules/AutoMoDeAdaptable.h>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_ADAPTABLE_H
#define AUTOMODE_ADAPTABLE_H

#include <argos3/core/simulator/simulator.h>

#include <vector>

namespace {
	using namespace argos;

	/**
	 * Selects the arm to pull according to the rewards obtained and the number of pulls.
	 * Implementation of the UCB1 algorithm. This function is visible only in the current file.
	 * 
	 * @param[in] rewards The cumulative reward obtained by each arm.
	 * @param[in] pulls The number of time each arm has been tried.
	 * @param[in] arms_count The total number of possible arms.
	 * @return The index of the arm (or value) selected to be used next.
	 */
	SInt32 SelectArm(const std::vector<Real> rewards, const std::vector<SInt32> pulls, int arms_count) {
		// accumulator variable for the total number of rounds
		SInt32 pulls_count = 0;

		// counts the total number of rounds
		for (SInt32 pull : pulls) {
			pulls_count += pull;
		}

		// the calculation of the confidence radius considers
		// the same nominator for all the arms
		Real nominator = 2 * log(pulls_count);

		// setup auxiliary variables to find the arm to pull
		Real max = 0;
		int max_idx = -1;

		// find the arm with the larger UCB
		for (int i = 0; i < arms_count; i++) {
			Real mu = rewards[i] / pulls[i];
			Real r = sqrt(nominator / pulls[i]);

			// if the arm “i” is more worth trying, select it
			if (mu + r > max) {
				max = mu + r;
				max_idx = i;
			}
		}

		return max_idx;
	}
}

namespace argos {
	/**
	 * Class representing a parameter which can assume multiple finite values at runtime. The value
	 * selection uses the Multi-Armed Bandit selection algorithm UCB1.
	 */
	template <typename T>
	class Adaptable {
		public:
			/**
			 * The empty class constructor. The instance is not usable before the call of the
			 * `Init` function.
			 */
			Adaptable() {}

			/**
			 * Take a single value that the parameter subject to adaptation can assume and
			 * initialize the support variables accordingly.
			 * @see CCI_Controller::Init for additional information.
			 * 
			 * @param[in] value The value that the parameter subject to adaptation can assume.
			 */
			void Init(T value) {
				m_tPossibleValues.clear();
				m_tPossibleValues.push_back(value);
				m_fRewards.clear();
				m_fRewards.push_back(1);
				m_iPulls.clear();
				m_iPulls.push_back(1);
			}

			/**
			 * Take multiple values that the parameter subject to adaptation can assume and
			 * initialize the support variables accordingly. The first element of the index is the
			 * first that will be tried.
			 * @see CCI_Controller::Init for additional information.
			 * 
			 * @param[in] possibleValues The possible values the parameter subject to adaptation
			 * can assume.
			 */
			void Init(std::vector<T> possibleValues) {
				m_tPossibleValues = std::vector<T>(possibleValues);
				m_fRewards = std::vector<Real>(possibleValues.size(), 1);
				m_iPulls = std::vector<SInt32>(possibleValues.size(), 1);
			}

			/**
			 * The operator that defines an implicit conversion between an instance of the class
			 * and the specified type T. Basically, it returns the currently selected value.
			 * 
			 * @return The value currently in use / selected.
			 */
			operator T () const
			{ 
				return m_tPossibleValues[m_iIndex]; 
			}

			/**
			 * Adapt the current value according to the received reward.
			 * 
			 * @param[in] reward Represent how well the current parameter performed.
			 */
			void Adapt(Real reward) {
				if (m_tPossibleValues.size() > 1) {
					m_fRewards[m_iIndex] += reward;
					m_iPulls[m_iIndex]++;
					m_iIndex = SelectArm(m_fRewards, m_iPulls, m_tPossibleValues.size());
				}
			}

		private:
			SInt32 m_iIndex = 0;				///< The index of the parameter currently in use.

			std::vector<T> m_tPossibleValues;	///< The possible values the parameter can assume.
			std::vector<Real> m_fRewards;		///< For each parameter-value, this array contains
 												///< the reward it has received.
			std::vector<SInt32> m_iPulls;		///< For each parameter-value, this array contains
 												///< the number of times it has been tried.
	};
}

#endif /* AUTOMODE_ADAPTABLE_H */
