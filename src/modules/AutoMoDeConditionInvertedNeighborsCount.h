/**
 * @file <src/modules/AutoMoDeConditionInvertedNeighborsCount.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_H
#define AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_H

#include "AutoMoDeCondition.h"
#include "AutoMoDeAdaptable.h"

namespace argos {
	class AutoMoDeConditionInvertedNeighborsCount: public AutoMoDeCondition {
		public:
			AutoMoDeConditionInvertedNeighborsCount();
			virtual ~AutoMoDeConditionInvertedNeighborsCount();

			AutoMoDeConditionInvertedNeighborsCount(AutoMoDeConditionInvertedNeighborsCount* pc_condition);

			/**
			 * @see AutoMoDeCondition::Clone
			 */
			virtual AutoMoDeConditionInvertedNeighborsCount* Clone();

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
			Adaptable<Real> m_fParameterEta;
			Adaptable<UInt8> m_unParameterXi;
	};
}

#endif /* AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_H */
