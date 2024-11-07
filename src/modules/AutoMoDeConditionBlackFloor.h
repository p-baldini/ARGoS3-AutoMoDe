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
#include "AutoMoDeAdaptable.h"

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
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			Real m_fGroundThreshold;
			Adaptable<Real> m_fProbability;
	};
}

#endif /* AUTOMODE_CONDITION_BLACK_FLOOR_H */
