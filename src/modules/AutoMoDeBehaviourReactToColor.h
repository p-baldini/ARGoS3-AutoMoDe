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

            void SetRobotDAO(EpuckDAO* pc_robot_dao) override;

        private:
            /**
             * The type of reaction the robot can have to the color.
             */
            enum ReactionType {
                FLEE_ANY,
                FLEE_COLOR,
                APPROACH_ANY,
                APPROACH_COLOR
            };

            CColor m_cColorEmitterParameter;
            AutoMoDeAdaptable<Real> m_cColorReceiverParameter;
            AutoMoDeAdaptable<Real> m_iReactionType;
            AutoMoDeAdaptable<Real> m_unReactionParameter;

            bool m_bBasicPerceptionCapabilities;	///< True if the robot can only analyze raw
													///< proximity data; False otherwise.
    };
}

#endif /* AUTOMODE_BEHAVIOUR_REACT_TO_COLOR_H */
