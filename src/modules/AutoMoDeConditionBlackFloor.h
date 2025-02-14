/**
 * @file <src/modules/AutoMoDeConditionBlackFloor.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_BLACK_FLOOR_H
#define AUTOMODE_CONDITION_BLACK_FLOOR_H

#include "AutoMoDeCondition.h"

namespace argos {
	class AutoMoDeConditionBlackFloor: public AutoMoDeCondition {
		public:
			AutoMoDeConditionBlackFloor();
			virtual ~AutoMoDeConditionBlackFloor();

			AutoMoDeConditionBlackFloor(AutoMoDeConditionBlackFloor* pc_condition);

			/**
			 * @see AutoMoDeCondition::Clone
			 */
			virtual AutoMoDeConditionBlackFloor* Clone();

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
			 * The threshold under which the ground is considered black.
			 */
			AutoMoDeValue /* Real */ m_fGroundThreshold;

			/**
			 * The probability to transition when the ground is black.
			 */
			AutoMoDeValue /* Real */ m_fProbability;

			/**
			 * True if the robot can only analyze raw ground data; False otherwise.
			 */
			bool m_bBasicPerceptionCapabilities;
	};
}

#endif /* AUTOMODE_CONDITION_BLACK_FLOOR_H */
