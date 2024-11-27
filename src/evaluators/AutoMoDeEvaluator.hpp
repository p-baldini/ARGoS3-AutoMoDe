/**
 * @file <src/modules/AutoMoDeEvaluator.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_EVALUATOR_HPP
#define AUTOMODE_EVALUATOR_HPP

#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_exception.h>

#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_proximity_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_sensor.h>

#include <argos3/demiurge/epuck-dao/EpuckDAO.h>

namespace argos {
    class AutoMoDeEvaluator {
        public:
            /**
             * The evaluator builder function. Returns an evaluator which type matches with the
             * required one.
             * 
             * @param[in] type The type of the evaluator to instantiate.
             * @return The desired type of evaluator.
             */
            static AutoMoDeEvaluator* Build(const std::string& type);

            /**
             * The class constructor. It initializes the evaluation time to the highest value.
             */
            AutoMoDeEvaluator();

            /**
             * Initialize the evaluator.
             */
            virtual void Init();

            /**
             * Method used to reset the status (variables) of the evaluator.
             */
            virtual void Reset();

            /**
             * Update the robot performance according to perception and action.
             */
            virtual void ControlStep();

            /**
             * The class constructor. It takes the indication on how often to adapt the parameter.
             * 
             * @param[in] evaluationTime The number of steps a parameter should be evaluated for.
             */
            virtual void SetEvaluationTime(UInt32 evaluationTime);

            /**
             * Start a new controller evaluation resetting the 'current performance' but
             * maintaining the 'cumulative performance'.
             */
            virtual void NewEvaluation();

            /**
             * Returns the performance computed since creation or reset.
             * 
             * @return The computed performance of the robot controller.
             */
            virtual Real CurrentPerformance();

            /**
             * Returns the cumulative performance since the beginning of the evaluation. This is
             * the sum of all the controllers performance.
             * 
             * @return The sum of the performances of all the evaluated controllers since creation.
             */
            virtual Real CumulativePerformance();

            /**
             * Getter for the label (name) of the evaluator.
             */
            const std::string& GetLabel();

            /**
             * Setter for the shared pointer to the representation of the robot state.
             */
            void SetRobotDAO(EpuckDAO* pc_robot_dao);

        protected:
            const std::string m_strLabel = "Dummy"; ///< The name of the evaluator; the default is
                                                    ///< "Dummy".
            UInt32 m_uEvaluationTime;               ///< The number of steps after which the
                                                    ///< parameter should adapt.
            UInt32 m_unEvaluationStep;              ///< The current evaluation step.
            EpuckDAO* m_pcRobotDAO;                 ///< Pointer to the state of the robot. Shared
                                                    ///< with the controller AutoMoDeController and
                                                    ///< the finite state machine
                                                    ///< AutoMoDeFiniteStateMachine.
    };
}

#endif /* AUTOMODE_EVALUATOR_HPP */
