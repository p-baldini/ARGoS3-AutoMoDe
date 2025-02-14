/**
 * @file <src/modules/AutoMoDeConditionProbColor.h>
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

namespace argos {
	class AutoMoDeConditionProbColor: public AutoMoDeCondition {
		public:
			/**
			 * Type of condition triggers. The condition can trigger if a specific color is
			 * perceived, if a specific color is not perceived, if any color is perceived, or if no
			 * color is perceived.
			 */
			enum TriggerType {
				SPECIFIC_COLOR_DETECTED,
				SPECIFIC_COLOR_UNDETECTED,
				ANY_COLOR_DETECTED,
				NO_COLOR_DETECTED
			};

			/**
			 * Class constructor. It sets up the condition name and some initially variables.
			 */
			AutoMoDeConditionProbColor();

			/**
			 * Class constructor. It creates the instance by coping another color condition.
			 */
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

		private:
			/**
			 * The type of event the condition activates for. The value is a reference to the enum.
			 */
			AutoMoDeValue /* UInt8  */ m_eTriggerType;

			/**
			 * The color the condition reacts to. The value is a reference to the color.
			 */
			AutoMoDeValue /* CColor */ m_cColorParameter;

			/**
			 * The probability of activating the transition when the condition holds.
			 */
			AutoMoDeValue /* Real   */ m_fProbability;

			/**
			 * The minimum distance the color must be. I suppose it is to avoid perceiving the self
			 * color (it was not described before).
			 */
			Real m_fDistance;
	};
}

#endif /* AUTOMODE_CONDITION_PROB_COLOR_H */
