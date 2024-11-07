/**
 * @file <src/modules/AutoMoDeConditionColor.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_PROB_COLOR_H
#define AUTOMODE_CONDITION_PROB_COLOR_H

#include "AutoMoDeCondition.h"
#include "AutoMoDeAdaptable.h"

namespace argos {
	class AutoMoDeConditionProbColor: public AutoMoDeCondition {
		public:
			AutoMoDeConditionProbColor();
			virtual ~AutoMoDeConditionProbColor();

			AutoMoDeConditionProbColor(AutoMoDeConditionProbColor* pc_condition);

			/**
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual AutoMoDeConditionProbColor* Clone();

			/**
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual bool Verify();

			/**
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual void Reset();

			/**
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual void Init();

			/**
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			CColor m_cColorParameter;
			Adaptable<Real> m_fProbability;
	};
}

#endif /* AUTOMODE_CONDITION_PROB_COLOR_H */
