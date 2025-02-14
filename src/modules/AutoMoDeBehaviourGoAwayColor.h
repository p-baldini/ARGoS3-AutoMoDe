/**
 * @file <src/modules/AutoMoDeBehaviourRepulsionColor.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_GO_AWAY_COLOR_H
#define AUTOMODE_BEHAVIOUR_GO_AWAY_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourGoAwayColor: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourGoAwayColor();
			AutoMoDeBehaviourGoAwayColor(AutoMoDeBehaviourGoAwayColor* pc_behaviour);
			virtual ~AutoMoDeBehaviourGoAwayColor();

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
			virtual AutoMoDeBehaviourGoAwayColor* Clone();

		private:
			/**
			 * The color emitted by the robot while in the go-away-color behavior.
			 */
			AutoMoDeValue /* CColor */ m_cColorEmitterParameter;

			/**
			 * The color the robot will flee.
			 */
			AutoMoDeValue /* CColor */ m_cColorReceiverParameter;

			/**
			 * The speed at which the robot will flee the color.
			 */
			AutoMoDeValue /* Real   */ m_unRepulsionParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_GO_AWAY_COLOR_H */
