/**
 * @file <src/core/AutoMoDeAdapter.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeAdapter.hpp"

#include <limits>

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeAdapter::AutoMoDeAdapter() {
		m_uEvaluationTime = 0;
		m_uElapsedTime = 0;
		m_uArmIndex = 0;
	}

	/****************************************/
	/****************************************/

	AutoMoDeAdapter::AutoMoDeAdapter(const AutoMoDeAdapter& other) {
		m_uEvaluationTime = other.m_uEvaluationTime;
		m_uElapsedTime = other.m_uElapsedTime;
		m_uArmIndex = other.m_uArmIndex;

		// set a copy of the parameters combinations
		for (auto combination : other.m_vParameterCombinations) {
			std::vector<Real> combinationCopy(combination);
			m_vParameterCombinations.push_back(combinationCopy);
		}

		// set a copy of the rewards and pulls data
		for (auto reward : other.m_fRewards) {
			m_fRewards.push_back(reward);
		}
		for (auto pull : other.m_iPulls) {
			m_iPulls.push_back(pull);
		}

		// set a copy of the active parameters value
		for (auto value : other.m_vActiveParameterValues) {
			m_vActiveParameterValues.push_back(value);
		}

		// set a copy of the static parameters value
		for (auto value : other.m_vStaticParameterValues) {
			m_vStaticParameterValues.push_back(value);
		}
	}

	/****************************************/
	/****************************************/

	AutoMoDeValue AutoMoDeAdapter::AddParameter(std::vector<Real> values) {
		// The initial value of each parameter is always the first
		Real* valuePointer;

		// if there is just 1 value, push it to the static parameters list
		if (values.size() == 1) {
			m_vStaticParameterValues.push_back(values[0]);
			valuePointer = &m_vStaticParameterValues.back();
		}
		// if there are more values, add them to the possible combinations
		else {
			// create a new vector that will replace the previous one
			std::vector<std::vector<Real>> newCombinations;

			// the number of combinations multiplies with the size of the `values` vector; e.g.:
			// old combinations <- [(1,2), (1,3)]
			// values <- [5, 6]
			// new combinations <- [(1,2,5), (1,2,6), (1,3,5), (1,3,6)]
			for (auto combination : m_vParameterCombinations) {
				for (auto value : values) {
					std::vector<Real> newCombination(combination);
					newCombination.push_back(value);
					newCombinations.push_back(newCombination);
				}
			}

			// replace the old combination vector with the new one
			m_vParameterCombinations = newCombinations;

			// increase the size of the rewards and pulls vectors by the number of new combinations
			m_fRewards.resize(newCombinations.size(), 0);
			m_iPulls.resize(newCombinations.size(), 0);

			// return the pointer to the currently used value of the parameter
			m_vActiveParameterValues.push_back(values[0]);
			valuePointer = &m_vActiveParameterValues.back();
		}

		// return the wrapper object 
		return AutoMoDeValue(valuePointer);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeAdapter::Adapt(Real reward) {
		// if there are no dynamic parameters, do nothing
		if (m_vParameterCombinations.size() == 0) {
			return;
		}

		// update the reward of the current arm (i.e., parameter)
		m_fRewards[m_uArmIndex] += reward;

		// if the evaluation epoch terminated, start a new one
		if (++m_uElapsedTime >= m_uEvaluationTime && m_vParameterCombinations.size() > 1) {
			m_uElapsedTime = 0;
			m_iPulls[m_uArmIndex]++;

			//
			// ARM SELECTION
			//

			// accumulator variable for the total number of rounds
    		SInt32 pullsCount = 0;

			// counts the total number of rounds
			for (SInt32 pull : m_iPulls) {
				pullsCount += pull;
			}

			// the calculation of the confidence radius considers
			// the same nominator for all the arms
			Real nominator = 2 * log(pullsCount);

			// setup auxiliary variables to find the arm to pull
			Real max = 0;
			m_uArmIndex = -1;

			// find the arm with the larger UCB or the first untested one
			for (long unsigned int i = 0; i < m_vParameterCombinations.size(); i++) {
				// the default setting for any arm is max range (i.e., unknown)
				Real mu = 0;
				Real r = std::numeric_limits<Real>::max();

				// if an arm has been tried before override the default priority
				if (m_iPulls[i] > 0) {
					mu = m_fRewards[i] / m_iPulls[i];
					r = sqrt(nominator / m_iPulls[i]);
				}

				// if the arm “i” is more worth trying, select it
				if (mu + r > max) {
					max = mu + r;
					m_uArmIndex = i;
				}
			}

			//
			// ARM SETTING
			//

			for (long unsigned int i = 0; i < m_vActiveParameterValues.size(); i++) {
				m_vActiveParameterValues[i] = m_vParameterCombinations[m_uArmIndex][i];
			}
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeAdapter::SetEvaluationTime(UInt32 evaluationTime) {
		m_uEvaluationTime = evaluationTime;
	}

	/****************************************/
	/****************************************/

	UInt32 AutoMoDeAdapter::GetEvaluationTime() const {
		return m_uEvaluationTime;
	}
}
