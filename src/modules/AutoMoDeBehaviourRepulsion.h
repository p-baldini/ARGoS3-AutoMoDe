/**
 * @file <src/modules/AutoMoDeBehaviourRepulsion.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_REPULSION_H
#define AUTOMODE_BEHAVIOUR_REPULSION_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourRepulsion: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourRepulsion();
			AutoMoDeBehaviourRepulsion(AutoMoDeBehaviourRepulsion* pc_behaviour);
			virtual ~AutoMoDeBehaviourRepulsion();

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
			virtual AutoMoDeBehaviourRepulsion* Clone();

		private:
			/**
			 * The speed at which the robot will flee others.
			 */
			AutoMoDeValue /* Real   */ m_unRepulsionParameter;

			/**
			 * The color emitted by the robot while in the repulsion behavior.
			 */
			AutoMoDeValue /* CColor */ m_cColorEmitterParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_REPULSION_H */
