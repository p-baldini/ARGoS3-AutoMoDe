/**
 * @file <src/modules/AutoMoDeBehaviourReactToColor.h>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H
#define AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H

#include "AutoMoDeBehaviour.h"

namespace argos {
    class AutoMoDeBehaviourReactToColor: public AutoMoDeBehaviour {
        public:
            /**
             * Class empty constructor.
             */
            AutoMoDeBehaviourReactToColor();

            /**
             * Class constructor accepting another behavior in input TODO why????
             * 
             * @param[in] pc_behaviour The behaviour to TODO ????
             */
            AutoMoDeBehaviourReactToColor(AutoMoDeBehaviourReactToColor* pc_behaviour);

            /**
             * Instance destructor.
             */
            virtual ~AutoMoDeBehaviourReactToColor();

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
            virtual AutoMoDeBehaviourReactToColor* Clone();

            /**
             * @see AutoMoDeBehavior::Adapt
             */
            virtual void Adapt(Real reward);

        private:
            /**
             * The type of reaction the robot can have to the color.
             */
            enum ReactionType {
                FLEE,
                APPROACH
            };

            CColor m_cColorEmitterParameter;
            CColor m_cColorReceiverParameter;
            AutoMoDeAdaptable<Real> m_iReactionType;
            AutoMoDeAdaptable<Real> m_unReactionParameter;
    };
}

#endif /* AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H */
