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

			/**
			 * @see AutoMoDeBehavior::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			CColor m_cColorEmitterParameter;
			CColor m_cColorReceiverParameter;
			AutoMoDeAdaptable<Real> m_unAttractionParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_GO_TO_COLOR_H */
