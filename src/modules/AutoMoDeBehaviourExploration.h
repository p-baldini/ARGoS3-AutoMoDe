/**
  * @file <src/modules/AutoMoDeBehaviourExploration.h>
  * 
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
  * 
  * @package ARGoS3-AutoMoDe
  * 
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EXPLORATION_H
#define AUTOMODE_BEHAVIOUR_EXPLORATION_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourExploration: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourExploration();
			AutoMoDeBehaviourExploration(AutoMoDeBehaviourExploration* pc_behaviour);
			virtual ~AutoMoDeBehaviourExploration();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourExploration* Clone();

		private:
			SInt32 m_unActionSteps;

			enum ExplorationState {
				GO_STRAIGHT,
				RANDOM_WALK,
				TURN
			};

			enum TurnDirection {
				LEFT,
				RIGHT
			};

			ExplorationState m_iStrategyType;
			ExplorationState m_eAction;
			TurnDirection m_eTurnDirection;

			Real m_fProximityThreshold;
			CRange<UInt32> m_cRandomStepsRange;
			Real m_fDistributionMu;
			Real m_fDistributionC;
            CColor m_cColorEmiterParameter;

			bool IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading);
	};
}

#endif
