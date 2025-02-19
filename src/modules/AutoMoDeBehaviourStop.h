/**
 * @file <src/modules/AutoMoDeBehaviourStop.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_STOP_H
#define AUTOMODE_BEHAVIOUR_STOP_H

#include "AutoMoDeBehaviour.h"

namespace argos {
	class AutoMoDeBehaviourStop: public AutoMoDeBehaviour {
		public:
			AutoMoDeBehaviourStop();
			AutoMoDeBehaviourStop(AutoMoDeBehaviourStop* pc_behaviour);
			virtual ~AutoMoDeBehaviourStop();

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
			virtual AutoMoDeBehaviourStop* Clone();

			/**
			 * @see AutoMoDeBehavior::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();

			/**
			 * @see AutoMoDeBehavior::Adapt
			 */
			virtual void Adapt(Real reward) {};

		private:
			/**
			 * The color the robot emits when performing this behavior.
			 */
			AutoMoDeValue<CColor> m_cColorEmitterParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_STOP_H */
