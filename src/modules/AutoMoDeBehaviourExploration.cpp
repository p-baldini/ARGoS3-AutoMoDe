/**
 * @file <src/modules/AutoMoDeBehaviourExploration.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourExploration.h"

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

#include <algorithm>

namespace argos {

	Real SampleLevy(CRandom::CRNG* rng, Real m_fDistributionMu, Real m_fDistributionC) {
		Real sample = rng->Gaussian(0, 1);
		return m_fDistributionMu + m_fDistributionC / (sample * sample);
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExploration::AutoMoDeBehaviourExploration() {
		m_strLabel = "Exploration";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExploration::AutoMoDeBehaviourExploration(AutoMoDeBehaviourExploration* pc_behaviour) {
		m_strLabel = pc_behaviour->GetLabel();
		m_bLocked = pc_behaviour->IsLocked();
		m_bOperational = pc_behaviour->IsOperational();
		m_unIndex = pc_behaviour->GetIndex();
		m_unIdentifier = pc_behaviour->GetIdentifier();
		m_mapParameters = pc_behaviour->GetParameters();
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExploration::~AutoMoDeBehaviourExploration() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourExploration* AutoMoDeBehaviourExploration::Clone() {
		return new AutoMoDeBehaviourExploration(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExploration::Init() {
		m_unActionSteps = 0;
		m_eAction = TURN;
		m_fProximityThreshold = 0.15;
		m_bLocked = false;

		m_iMaxTurningSteps = FindParameter("rwm");
		m_iStrategyType = FindParameter("rwt");
		m_fDistributionMu = FindParameter("rwmu", AutoMoDeValue());
		m_fDistributionC = FindParameter("rwc", AutoMoDeValue());

		m_cColorEmitterParameter = FindParameter("cle", AutoMoDeValue());
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExploration::ControlStep() {
		// if the selected action is "go_straight", set the wheels to go straight ahead
		if (m_eAction == GO_STRAIGHT || m_eAction == RANDOM_WALK) {
			m_pcRobotDAO->SetWheelsVelocity( m_pcRobotDAO->GetMaxVelocity(),  m_pcRobotDAO->GetMaxVelocity());
		}
		else
		// if the selected action is "turn" and the direction left, set the wheels to turn anti-clockwise
		if (m_eAction == TURN && m_eTurnDirection == LEFT) {
			m_pcRobotDAO->SetWheelsVelocity(-m_pcRobotDAO->GetMaxVelocity(),  m_pcRobotDAO->GetMaxVelocity());
		}
		else
		// if the selected action is "turn" and the direction right, set the wheels to turn clockwise
		if (m_eAction == TURN && m_eTurnDirection == RIGHT) {
			m_pcRobotDAO->SetWheelsVelocity( m_pcRobotDAO->GetMaxVelocity(), -m_pcRobotDAO->GetMaxVelocity());
		}

		// decrease the remaining number of steps during which the selected action should be performed
		m_unActionSteps--;

		// if the "random_walk" time terminated, performs a turn
		// for a random amount of steps (uniform distr) in a random direction
		if (m_unActionSteps <= 0 && m_eAction == RANDOM_WALK) {
			m_unActionSteps = (m_pcRobotDAO->GetRandomNumberGenerator())->Uniform(CRange<UInt32>(0, (UInt32) m_iMaxTurningSteps)) + 1;
			if ((m_pcRobotDAO->GetRandomNumberGenerator())->Uniform(CRange<UInt32>(0, 1)) < 0.5) {
				m_eTurnDirection = LEFT;
			}
			else {
				m_eTurnDirection = RIGHT;
			}
			m_eAction = TURN;
		}

		// if the "turn" time terminated, go straight for a random amount of steps (Levy distr)
		if (m_unActionSteps <= 0 && m_eAction == TURN) {
			m_unActionSteps = SampleLevy(m_pcRobotDAO->GetRandomNumberGenerator(), m_fDistributionMu, m_fDistributionC) + 1;
			m_eAction = (UInt8) m_iStrategyType == 0 ? GO_STRAIGHT : RANDOM_WALK;
		}

		// if the robot perceives an obstacle while going straight, performs a turn
		// for a random amount of steps (uniform distr) in a direction opposite to the obstacle
		if (m_bBasicPerceptionCapabilities) {
			if (m_eAction != TURN && IsObstacleInFront(m_pcRobotDAO->GetProximityInput())) {
				// set the number of steps the robot has to turn
				CRange<UInt32> turnRange(0, (UInt32) m_iMaxTurningSteps);
				m_unActionSteps = m_pcRobotDAO->GetRandomNumberGenerator()->Uniform(turnRange);

				// set the direction of the turn: if the perceived object is on the right, turn
				// left; otherwise turn right
				auto values = m_pcRobotDAO->GetProximityInput();
				CCI_EPuckProximitySensor::TReadings right(
					values.begin(),
					values.begin() + values.size() / 2
				);
				m_eTurnDirection = IsObstacleInFront(right) ? LEFT : RIGHT;
				m_eAction = TURN;
			}
		}
		else {
			if (m_eAction != TURN && IsObstacleInFront(m_pcRobotDAO->GetProximityReading())) {
				// set the number of steps the robot has to turn
				CRange<UInt32> turnRange(0, (UInt32) m_iMaxTurningSteps);
				m_unActionSteps = m_pcRobotDAO->GetRandomNumberGenerator()->Uniform(turnRange);

				// set the direction of the turn according to the direction vector
				CRadians cAngle = m_pcRobotDAO->GetProximityReading().Angle.SignedNormalize();
				m_eTurnDirection = cAngle.GetValue() < 0 ? LEFT : RIGHT;
				m_eAction = TURN;
			}
		}

		m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExploration::Reset() {
		m_bOperational = false;
		Init();
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExploration::ResumeStep() {
		m_bOperational = true;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourExploration::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		AutoMoDeBehaviour::SetRobotDAO(pc_robot_dao);
		m_bBasicPerceptionCapabilities = (
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel1Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot1) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel2Dot2) ||
			typeid(*m_pcRobotDAO) == typeid(ReferenceModel3DotS)
		);
	}

	/****************************************/
	/****************************************/

	bool AutoMoDeBehaviourExploration::IsObstacleInFront(
		CCI_EPuckProximitySensor::TReadings t_prox_readings
	) {
		auto discriminator = [this](auto o){
			return  o.Value >= m_fProximityThreshold &&
					o.Angle <= CRadians::PI_OVER_TWO &&
					o.Angle >= -CRadians::PI_OVER_TWO;
		};
		return std::any_of(t_prox_readings.begin(), t_prox_readings.end(), discriminator);
	}

	bool AutoMoDeBehaviourExploration::IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading) {
		CRadians cAngle = s_prox_reading.Angle;
		return s_prox_reading.Value >= m_fProximityThreshold
			&& ((cAngle <= CRadians::PI_OVER_TWO) && (cAngle >= -CRadians::PI_OVER_TWO));
	}
}
