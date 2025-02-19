/**
 * @file <src/modules/AutoMoDeCondition.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#ifndef AUTOMODE_CONDITION_H
#define AUTOMODE_CONDITION_H

#include "../core/AutoMoDeParameters.hpp"

#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>

#include <argos3/demiurge/epuck-dao/EpuckDAO.h>

#include <map>

namespace argos {
	class AutoMoDeCondition {
		protected:
			/**
			 * Index of the behaviour at the origin of the condition.
			 */
			UInt32 m_unFromBehaviourIndex;

			/**
			 * Index of the behaviour at the extremity of the condition.
			 */
			UInt32 m_unToBehaviourIndex;

			/**
			 * Name of the condition.
			 */
			std::string m_strLabel;

			/**
			 * Index of the condition.
			 */
			UInt32 m_unIndex;

			/**
			 * Identifier of the condition.
			 */
			UInt32 m_unIdentifier;

			/**
			 * Shared pointer to the state of the robot.
			 */
			EpuckDAO* m_pcRobotDAO;

			/**
			 * Reference to the object managing the FSM parameters.
			 */
			AutoMoDeParameters* m_Parameters;

			/**
			 * True if the robot has basic perception capabilities, false if it pre-process the
			 * sensory input to provide a more stable perception. Used to select which method to
			 * call.
			 */
			bool m_bBasicPerceptionCapabilities;

		public:

			AutoMoDeCondition();

			AutoMoDeCondition(const AutoMoDeCondition* other);

			virtual ~AutoMoDeCondition(){};

			/**
			 * Tests whether the condition evaluates to true or false.
			 */
			virtual bool Verify() = 0;

			/**
			 * Reset method.
			 */
			virtual void Reset() = 0;

			/**
			 * Initialize the condition.
			 */
			virtual void Init() = 0;

			/**
			 * Cloning method.
			 */
			virtual AutoMoDeCondition* Clone() = 0;

			/**
			 * Returns the DOT description of the condition.
			 */
			virtual const std::string GetDOTDescription() = 0;

			/**
			 * Set the parameters manager.
			 * 
			 * @param[in] parameters The object containing the FSM parameters.
			 */
			void SetParameters(AutoMoDeParameters* parameters);

			/**
			 * Setters for the origin and extremity behaviours of the condition.
			 */
			void SetOriginAndExtremity(const UInt32& un_from, const UInt32& un_to);
			void SetOrigin(const UInt32& un_from);
			void SetExtremity(const UInt32& un_to);

			/**
			 * Setter and getter for the index of the condition.
			 */
			void SetIndex(const UInt32& un_index);
			const UInt32& GetIndex() const;

			/**
			 * Getters for the origin and extremity behaviour of the condition.
			 */
			const UInt32& GetOrigin() const;
			const UInt32& GetExtremity() const;

			/**
			 * Getter and setter for the identifier of the condition.
			 */
			void SetIdentifier(const UInt32& un_id);
			const UInt32& GetIdentifier() const;

			/**
			 * Getter for the name of the label.
			 */
			const std::string& GetLabel() const;

			/**
			 * Setter for the pointer to the robot state.
			 */
			virtual void SetRobotDAO(EpuckDAO* pc_robot_dao);

			/**
			 * Returns a random value from a Bernoulli distribution.
			 */
			bool EvaluateBernoulliProbability(const Real& f_probability) const;

			/**
			 * Data transform for color of the LEDs.
			 */
			CColor GetColorParameter(const UInt32 &un_value);
	};
}

#endif /* AUTOMODE_CONDITION_H */
