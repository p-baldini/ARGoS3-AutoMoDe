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

			/**
			 * @see AutoMoDeBehavior::Adapt
			 */
			virtual void Adapt(Real reward);

		private:
			CColor m_cColorEmitterParameter;
			CColor m_cColorReceiverParameter;
			AutoMoDeAdaptable<Real> m_unRepulsionParameter;
	};
}

#endif /* AUTOMODE_BEHAVIOUR_GO_AWAY_COLOR_H */
