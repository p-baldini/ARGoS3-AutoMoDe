/**
 * @file <src/modules/AutoMoDeAdaptable.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_ADAPTABLE_HPP
#define AUTOMODE_ADAPTABLE_HPP

#include <argos3/core/simulator/simulator.h>

#include <vector>

namespace argos {
    /**
     * Class representing a parameter which can assume multiple finite values at runtime. The value
     * selection uses the Multi-Armed Bandit selection algorithm UCB1.
     */
    template <typename T>
    class AutoMoDeAdaptable {
        public:
            /**
             * Copy the adaptable instance so that afterwards any modification remains confined to
             * the specific instance.
             * 
             * @param[in] origin The adaptable instance to clone.
             * @return A deep copy of the adaptable instance.
             */
            static AutoMoDeAdaptable<T> Clone(const AutoMoDeAdaptable<T>& origin);

            /**
             * Take a single value that the parameter subject to adaptation can assume and
             * initialize the support variables accordingly.
             * @see CCI_Controller::Init for additional information.
             * 
             * @param[in] value The value that the parameter subject to adaptation can assume.
             */
            void Init(T value);

            /**
             * Take multiple values that the parameter subject to adaptation can assume and
             * initialize the support variables accordingly. The first element of the index is the
             * first that will be tried.
             * @see CCI_Controller::Init for additional information.
             * 
             * @param[in] possibleValues The possible values the parameter subject to adaptation
             * can assume.
             */
            void Init(std::vector<T> possibleValues);

            /**
             * The operator that defines an implicit conversion between an instance of the class
             * and the specified type T. Basically, it returns the currently selected value.
             * 
             * @return The value currently in use / selected.
             */
            operator T () const;

            /**
             * Adapt the current value according to the received reward.
             * 
             * @param[in] reward Represent how well the current parameter performed.
             */
            void Adapt(Real reward);

        private:
            SInt32 m_iIndex = 0;                ///< The index of the parameter currently in use.

            std::vector<T> m_tPossibleValues;   ///< The possible values the parameter can assume.
            std::vector<Real> m_fRewards;       ///< For each parameter-value, this array contains
                                                ///< the reward it has received.
            std::vector<SInt32> m_iPulls;       ///< For each parameter-value, this array contains
                                                ///< the number of times it has been tried.

            /**
             * Selects the arm to pull according to the rewards obtained and the number of pulls.
             * Implementation of the UCB1 algorithm.
             * 
             * @return The index of the arm (or value) selected to be used next.
             */
            SInt32 SelectArm();
    };

    #include "AutoMoDeAdaptable.cpp"
}

#endif /* AUTOMODE_ADAPTABLE_HPP */
