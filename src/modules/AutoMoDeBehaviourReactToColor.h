/**
 * @file <src/modules/AutoMoDeBehaviourReactToColor.h>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H
#define AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourReactToColor: public AutoMoDeBehaviour {
		public:
			/**
			 * Class empty constructor.
			 */
			AutoMoDeBehaviourReactToColor();

			/**
			 * Class constructor accepting another behavior in input TODO why????
			 * 
			 * @param[in] pc_behaviour The behaviour to TODO ????
			 */
			AutoMoDeBehaviourReactToColor(AutoMoDeBehaviourReactToColor* pc_behaviour);

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
			virtual AutoMoDeBehaviourReactToColor* Clone();

			/**
			 * @see AutoMoDeBehavior::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();

			/**
			 * @see AutoMoDeBehavior::SetRobotDAO
			 */
			void SetRobotDAO(EpuckDAO* pc_robot_dao) override;

		private:
			/**
			 * The type of reaction the robot can have to the color.
			 */
			enum ReactionType {
				FLEE_ANY,
				FLEE_COLOR,
				APPROACH_ANY,
				APPROACH_COLOR
			};

			/**
			 * The color emitted by the robot when using this behavior.
			 */
			AutoMoDeValue<CColor> m_cColorEmitterParameter;

			/**
			 * The color that the robot reacts to when using this behavior.
			 */
			AutoMoDeValue<CColor> m_cColorReceiverParameter;

			/**
			 * The type of reaction the robot has to (possibly lack of) color.
			 */
			AutoMoDeValue<UInt8> m_iReactionType;

			/**
			 * The speed at which the robot approach / flee the color.
			 */
			AutoMoDeValue<Real> m_unReactionParameter;

			/**
			 * True if the robot can only analyze raw proximity data; False otherwise.
			 */
			bool m_bBasicPerceptionCapabilities;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H */
