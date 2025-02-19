/**
 * @file <src/modules/AutoMoDeBehaviourPhototaxis.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_PHOTOTAXIS_H
#define AUTOMODE_BEHAVIOUR_PHOTOTAXIS_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourPhototaxis: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourPhototaxis();
			AutoMoDeBehaviourPhototaxis(AutoMoDeBehaviourPhototaxis* pc_behaviour);
			virtual ~AutoMoDeBehaviourPhototaxis();

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
			virtual AutoMoDeBehaviourPhototaxis* Clone();

			/**
			 * @see AutoMoDeBehavior::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();
	};
}

#endif /* AUTOMODE_BEHAVIOUR_PHOTOTAXIS_H */
