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
			 * @see AutoMoDeBehavior::GetDOTDescription
			 */
			virtual const std::string GetDOTDescription();

		private:
			/**
			 * The speed at which the robot will approach others.
			 */
			AutoMoDeValue<Real> m_unAttractionParameter;

			/**
			 * The color emitted by the robot while in the attraction behavior.
			 */
			AutoMoDeValue<CColor> m_cColorEmitterParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_ATTRACTION_H */
