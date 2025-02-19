/**
 * @file <src/modules/AutoMoDeConditionFixedProbability.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_FIXED_PROBABILITY_H
#define AUTOMODE_CONDITION_FIXED_PROBABILITY_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionFixedProbability: public AutoMoDeCondition {
		public:
			AutoMoDeConditionFixedProbability();
			virtual ~AutoMoDeConditionFixedProbability();

			AutoMoDeConditionFixedProbability(AutoMoDeConditionFixedProbability* pc_condition);

			/**
			 * @see AutoMoDeCondition::Clone
			 */
			virtual AutoMoDeConditionFixedProbability* Clone();
		
			/**
			 * @see AutoMoDeCondition::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();

			/**
			 * @see AutoMoDeCondition::Verify
			 */
			virtual bool Verify();

			/**
			 * @see AutoMoDeCondition::Reset
			 */
			virtual void Reset();

			/**
			 * @see AutoMoDeCondition::Init
			 */
			virtual void Init();

		private:
			/**
			 * The probability for the transition to enable.
			 */
			AutoMoDeValue<Real> m_fProbability;
	};
}

#endif /* AUTOMODE_CONDITION_FIXED_PROBABILITY_H */
