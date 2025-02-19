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

			/**
			 * @see AutoMoDeBehavior::ControlStep
			 */
			virtual void ControlStep();

			/**
			 * @see AutoMoDeBehavior::Reset
			 */
			virtual void Reset();

			/**
			 * @see AutoMoDeBehavior::ResumeStep
			 */
			virtual void ResumeStep();

			/**
			 * @see AutoMoDeBehavior::Init
			 */
			virtual void Init();

			/**
			 * @see AutoMoDeBehavior::Clone
			 */
			virtual AutoMoDeBehaviourExploration* Clone();

			/**
			 * @see AutoMoDeBehavior::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();

			/**
			 * @see AutoMoDeBehavior::SetRobotDAO
			 */
			void SetRobotDAO(EpuckDAO* pc_robot_dao) override;

		private:
			SInt32 m_unActionSteps;

			/**
			 * The motion strategies employed by the exploration behavior.
			 */
			enum ExplorationState {
				GO_STRAIGHT,
				RANDOM_WALK,
				TURN
			};

			/**
			 * The possible directions of a turn.
			 */
			enum TurnDirection {
				LEFT,
				RIGHT
			};

			/**
			 * Indicate the exploration strategy employed; adaptable parameter of the behaviour: if
			 * instantiated with more than one value, it can chose which to use at runtime.
			 */
			AutoMoDeValue<UInt8> m_iStrategyType;

			/**
			 * Indicate the maximum number of steps the robot can turn; adaptable parameter of the
			 * behaviour: if instantiated with more than one value, it can chose which to use at
			 * runtime.
			 */
			AutoMoDeValue<UInt32> m_iMaxTurningSteps;

			/**
			 * The mean of the Levy distribution; adaptable parameter of the behaviour: if
			 * instantiated with more than one value, it can chose which to use at runtime.
			 */
			AutoMoDeValue<Real> m_fDistributionMu;

			/**
			 * The std dev of the Levy distribution; adaptable parameter of the behaviour: if
			 * instantiated with more than one value, it can chose which to use at runtime.
			 */
			AutoMoDeValue<Real> m_fDistributionC;

			/**
			 * True if the robot can only analyze raw proximity data; False otherwise.
			 */
			bool m_bBasicPerceptionCapabilities;

			/**
			 * The current action under use in [turn, go_straight, random_walk]
			 */
			ExplorationState m_eAction;

			/**
			 * The remaining step-duration of the current action.
			 */
			TurnDirection m_eTurnDirection;

			/**
			 * The color emitted by the robot.
			 */
			AutoMoDeValue<CColor> m_cColorEmitterParameter;

			/**
			 * The threshold upon which an object is considered a near obstacle.
			 */
			Real m_fProximityThreshold;

			/**
			 * Return true is the robot perceives an obstacle in the proximity threshold.
			 * 
			 * @param[in] s_prox_reading The proximity readings of the robot.
			 * @return True if the robot perceives an obstacle in range, false otherwise.
			 */
			bool IsObstacleInFront(CCI_EPuckProximitySensor::TReadings t_prox_readings);

			/**
			 * Return true is the robot perceives an obstacle in the proximity threshold.
			 * 
			 * @param[in] s_prox_reading The proximity readings of the robot.
			 * @return True if the robot perceives an obstacle in range, false otherwise.
			 */
			bool IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading);
	};
}

#endif /* AUTOMODE_BEHAVIOUR_EXPLORATION_H */
