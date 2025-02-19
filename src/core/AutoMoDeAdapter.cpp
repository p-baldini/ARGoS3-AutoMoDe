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
		m_uEvaluationTime = std::numeric_limits<UInt32>::max();
		m_uElapsedTime = 0;
		m_uArmIndex = 0;
	}

	/****************************************/
	/****************************************/

	AutoMoDeAdapter::AutoMoDeAdapter(const AutoMoDeAdapter& other) {
		m_uEvaluationTime = other.m_uEvaluationTime;
		m_uElapsedTime = other.m_uElapsedTime;
		m_uArmIndex = other.m_uArmIndex;

		// set a copy of the rewards and pulls data
		for (auto reward : other.m_fRewards) {
			m_fRewards.push_back(reward);
		}
		for (auto pull : other.m_iPulls) {
			m_iPulls.push_back(pull);
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeAdapter::Adapt(Real reward) {
		// if there number of arm is greater than 0, select one to try
		if (! m_fRewards.empty()) {
			// update the reward of the current arm
			m_fRewards[m_uArmIndex] += reward;

			// if the evaluation epoch terminated, start a new one
			if (++m_uElapsedTime >= m_uEvaluationTime) {
				m_uElapsedTime = 0;
				m_iPulls[m_uArmIndex]++;

				m_uArmIndex = SelectArm();

				SetValues(m_uArmIndex);
			}
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeAdapter::SetArmsCount(UInt32 arms_count) {
		m_fRewards = std::vector<Real>(arms_count, 0);
		m_iPulls = std::vector<UInt32>(arms_count, 0);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeAdapter::SetEvaluationTime(UInt32 evaluationTime) {
		m_uEvaluationTime = evaluationTime;
	}

	/****************************************/
	/****************************************/

	UInt32 AutoMoDeAdapter::SelectArm() {
		// accumulator variable for the total number of rounds
		UInt32 pullsCount = 0;

		// counts the total number of rounds and checks whether an arm has never been pulled
		// if an arm has never been pulled, it will be tested next
		for (unsigned long int i = 0; i < m_iPulls.size(); i++) {
			pullsCount += m_iPulls[i];

			if (m_iPulls[i] == 0) {
				return i;
			}
		}

		// the calculation of the confidence radius considers
		// the same nominator for all the arms
		Real nominator = 2 * log(pullsCount);

		// setup auxiliary variables to find the arm to pull
		Real max = 0;
		UInt32 arm = -1;

		// find the arm with the larger UCB or the first untested one
		for (long unsigned int i = 0; i < m_fRewards.size(); i++) {
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
				arm = i;
			}
		}

		return arm;
	}
}
