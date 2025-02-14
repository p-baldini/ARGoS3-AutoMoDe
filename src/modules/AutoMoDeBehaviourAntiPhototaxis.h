/**
 * @file <src/modules/AutoMoDeBehaviourAntiPhototaxis.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_H
#define AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAntiPhototaxis: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAntiPhototaxis();
			AutoMoDeBehaviourAntiPhototaxis(AutoMoDeBehaviourAntiPhototaxis* pc_behaviour);
			virtual ~AutoMoDeBehaviourAntiPhototaxis();

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
			virtual AutoMoDeBehaviourAntiPhototaxis* Clone();
	};
}

#endif /* AUTOMODE_BEHAVIOUR_ANTI_PHOTOTAXIS_H */
