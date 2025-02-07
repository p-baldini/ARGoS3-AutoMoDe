/**
 * @file <src/modules/AutoMoDeEvaluatorForaging.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_EVALUATOR_FORAGING_HPP
#define AUTOMODE_EVALUATOR_FORAGING_HPP

#include "AutoMoDeEvaluator.hpp"

namespace argos {
    class AutoMoDeEvaluatorForaging : public AutoMoDeEvaluator {
        public:
            /**
             * The class destructor. Prints the final performance before exiting.
             */
            ~AutoMoDeEvaluatorForaging();

            /**
             * @see AutoMoDeEvaluator::Init
             */
            void Init();

            /**
             * @see AutoMoDeEvaluator::Reset
             */
            void Reset();

            /**
             * Count the number of times the robot visited the foraging area without holding a
             * prey, and the number of times it visited the nest while holding a prey.
             * Additionally, provide a prey if the robot visit the foraging area without holding a
             * prey, and take it if the robot visit the nest while holding a prey.
             * 
             * @see AutoMoDeEvaluator::ControlStep
             */
            void ControlStep();

            /**
             * @see AutoMoDeEvaluator::NewEvaluation
             */
            void NewEvaluation();

            /**
             * @see AutoMoDeEvaluator::CurrentPerformance
             */
            Real CurrentPerformance();

            /**
             * @see AutoMoDeEvaluator::CumulativePerformance
             */
            Real CumulativePerformance();

        protected:
            const std::string m_strLabel = "Foraging";  ///< The name of the evaluator.
            Real m_fCurrentPerformance;                 ///< The current performance of the
                                                        ///< solution.
            Real m_fCumulativePerformance;              ///< The performance of the robot since the
                                                        ///< first evaluation.
            bool m_bHasPrey;                            ///< True if the robot visited the foraging
                                                        ///< area but not the nest; False otherwise.
    };
}

#endif /* AUTOMODE_EVALUATOR_FORAGING_HPP */
