/**
 * @file <src/modules/AutoMoDeConditionFloorColor.h>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_FLOOR_COLOR_HPP
#define AUTOMODE_CONDITION_FLOOR_COLOR_HPP

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionFloorColor: public AutoMoDeCondition {
		public:
			/**
			 * Class constructor. Sets the condition string.
			 */
			AutoMoDeConditionFloorColor();

			/**
			 * Copy constructor. Create a new condition equal to the passed one.
			 * 
			 * @param[in] pc_condition The condition to copy.
			 */
			AutoMoDeConditionFloorColor(AutoMoDeConditionFloorColor* pc_condition);

			/**
			 * @see AutoMoDeCondition::Clone
			 */
			virtual AutoMoDeConditionFloorColor* Clone();

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
			 * The type of perception that enables the transition. 0 means that the presence of the
			 * color enables the transition, 1 that it is enabled by its absence.
			 */
			AutoMoDeValue /* UInt8  */ m_eType;

			/**
			 * The average value of the ground color the transition is sensible to. The transition
			 * is enabled if the perceived value is in m_fGroundColor +- 0.25.
			 */
			AutoMoDeValue /* Real   */ m_fGroundColor;

			/**
			 * The probability of the transition to enable when the robot perceived the desired
			 * ground color.
			 */
			AutoMoDeValue /* Real   */ m_fProbability;
	};
}

#endif /* AUTOMODE_CONDITION_FLOOR_COLOR_HPP */
