/**
 * @file <src/modules/AutoMoDeBehaviourAttractionColor.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_GO_TO_COLOR_H
#define AUTOMODE_BEHAVIOUR_GO_TO_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourGoToColor: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourGoToColor();
			AutoMoDeBehaviourGoToColor(AutoMoDeBehaviourGoToColor* pc_behaviour);
			virtual ~AutoMoDeBehaviourGoToColor();

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
			virtual AutoMoDeBehaviourGoToColor* Clone();

		private:
			/**
			 * The color emitted by the robot while in the go-to-color behavior.
			 */
			AutoMoDeValue /* CColor */ m_cColorEmitterParameter;

			/**
			 * The color the robot will approach.
			 */
			AutoMoDeValue /* CColor */ m_cColorReceiverParameter;

			/**
			 * The speed at which the robot will approach the color.
			 */
			AutoMoDeValue /* Real   */ m_unAttractionParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_GO_TO_COLOR_H */
