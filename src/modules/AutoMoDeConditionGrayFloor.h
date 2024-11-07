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
#include "AutoMoDeAdaptable.h"

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
			 * @see AutoMoDeCondition::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			CRange<Real> m_fGroundThresholdRange;
			Adaptable<Real> m_fProbability;
	};
}

#endif /* AUTOMODE_CONDITION_GRAY_FLOOR_H */
