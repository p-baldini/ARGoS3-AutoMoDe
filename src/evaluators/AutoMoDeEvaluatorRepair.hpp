/**
 * @file <src/modules/AutoMoDeEvaluatorRepair.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_EVALUATOR_REPAIR_HPP
#define AUTOMODE_EVALUATOR_REPAIR_HPP

#include "AutoMoDeEvaluator.hpp"

namespace argos {
    class AutoMoDeEvaluatorRepair : public AutoMoDeEvaluator {
        public:
            /**
             * @see AutoMoDeEvaluator::Init
             */
            void Init();

            /**
             * @see AutoMoDeEvaluator::Reset
             */
            void Reset();

            /**
             * Check the Range and Bearing for received rewards.
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
            const std::string m_strLabel = "Repair";    ///< The name of the evaluator.
            Real m_fCurrentPerformance;                 ///< The current performance of the
                                                        ///< solution.
            Real m_fCumulativePerformance;              ///< The performance of the robot since the
                                                        ///< first evaluation.

            std::map<UInt8, UInt8> un_mMessageIDs;      ///< For each object in the environment,
                                                        ///< the ID of its last message received.
                                                        ///< This to avoid reading multiple time
                                                        ///< the same message.
    };
}

#endif /* AUTOMODE_EVALUATOR_REPAIR_HPP */
