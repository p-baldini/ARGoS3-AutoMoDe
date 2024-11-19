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
#include "AutoMoDeAdaptable.hpp"

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

			/**
			 * @see AutoMoDeBehavior::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			AutoMoDeAdaptable<Real> m_unRepulsionParameter;
            CColor m_cColorEmitterParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_REPULSION_H */
