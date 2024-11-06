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
		m_fProximityThreshold = 0.1;
		m_bLocked = false;

		std::map<std::string, Real>::iterator it = m_mapParameters.find("rwm");
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter for the following behaviour: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		m_cRandomStepsRange.SetMax(it->second);

		it = m_mapParameters.find("rwt");
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter for the following behaviour: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		m_iStrategyType = it->second == 0 ? GO_STRAIGHT : RANDOM_WALK;

		it = m_mapParameters.find("rwmu");
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter for the following behaviour: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		m_fDistributionMu = it->second;

		it = m_mapParameters.find("rwc");
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter for the following behaviour: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		m_fDistributionC = it->second;

		it = m_mapParameters.find("cle");
		if (it == m_mapParameters.end()) {
			LOGERR << "[FATAL] Missing parameter for the following behaviour: " << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
		m_cColorEmiterParameter = GetColorParameter(it->second, true);
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
			m_unActionSteps = (m_pcRobotDAO->GetRandomNumberGenerator())->Uniform(m_cRandomStepsRange) + 1;
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
			m_eAction = m_iStrategyType;
		}

		// if the robot perceives an obstacle while going straight, performs a turn
		// for a random amount of steps (uniform distr) in a direction opposite to the obstacle
		if (m_eAction != TURN && IsObstacleInFront(m_pcRobotDAO->GetProximityReading())) {
			m_unActionSteps = (m_pcRobotDAO->GetRandomNumberGenerator())->Uniform(m_cRandomStepsRange);
			CRadians cAngle = m_pcRobotDAO->GetProximityReading().Angle.SignedNormalize();
			if (cAngle.GetValue() < 0) {
				m_eTurnDirection = LEFT;
			} else {
				m_eTurnDirection = RIGHT;
			}
			m_eAction = TURN;
		}

		m_pcRobotDAO->SetLEDsColor(m_cColorEmiterParameter);
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

	bool AutoMoDeBehaviourExploration::IsObstacleInFront(CCI_EPuckProximitySensor::SReading s_prox_reading) {
		CRadians cAngle = s_prox_reading.Angle;
		if (s_prox_reading.Value >= m_fProximityThreshold && ((cAngle <= CRadians::PI_OVER_TWO) && (cAngle >= -CRadians::PI_OVER_TWO))) {
			return true;
		}
		return false;
	}
}
