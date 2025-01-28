/**
 * @file <src/modules/AutoMoDeBehaviourAttraction.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_ATTRACTION_H
#define AUTOMODE_BEHAVIOUR_ATTRACTION_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourAttraction: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourAttraction();
			AutoMoDeBehaviourAttraction(AutoMoDeBehaviourAttraction* pc_behaviour);
			virtual ~AutoMoDeBehaviourAttraction();

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
			virtual AutoMoDeBehaviourAttraction* Clone();

			/**
			 * @see AutoMoDeBehavior::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			Real m_unAttractionParameter;
			CColor m_cColorEmitterParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_ATTRACTION_H */
