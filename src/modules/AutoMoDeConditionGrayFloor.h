/**
 * @file <src/modules/AutoMoDeConditionGrayFloor.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_GRAY_FLOOR_H
#define AUTOMODE_CONDITION_GRAY_FLOOR_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionGrayFloor: public AutoMoDeCondition {
		public:
			AutoMoDeConditionGrayFloor();
			virtual ~AutoMoDeConditionGrayFloor();

			AutoMoDeConditionGrayFloor(AutoMoDeConditionGrayFloor* pc_condition);

			/**
			 * @see AutoMoDeCondition::Clone
			 */
			virtual AutoMoDeConditionGrayFloor* Clone();

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

			/**
			 * @see AutoMoDeCondition::SetRobotDAO
			 */
			void SetRobotDAO(EpuckDAO* pc_robot_dao) override;

		private:
			/**
			 * The range into which the ground is considered gray.
			 */
			CRange<Real> m_fGroundThresholdRange;

			/**
			 * The probability to transition when the ground is gray.
			 */
			AutoMoDeValue /* Real */ m_fProbability;

			/**
			 * True if the robot can only analyze raw ground data; False otherwise.
			 */
			bool m_bBasicPerceptionCapabilities;
	};
}

#endif /* AUTOMODE_CONDITION_GRAY_FLOOR_H */
