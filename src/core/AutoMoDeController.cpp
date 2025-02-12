/**
 * @file <src/core/AutoMoDeController.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeController.h"

#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel1Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot0.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot1.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot2.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel2Dot3.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3Dot0.h>
#include <argos3/demiurge/epuck-dao/ReferenceModel3DotS.hpp>

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeController::AutoMoDeController() {
		m_pcRobotState = new ReferenceModel3DotS();
		m_unTimeStep = 0;
		m_strFsmConfiguration = "";
		m_bMaintainHistory = false;
		m_bPrintReadableFsm = false;
		m_strHistoryFolder = "./";
		m_bFiniteStateMachineGiven = false;
	}

	/****************************************/
	/****************************************/

	AutoMoDeController::~AutoMoDeController() {
		delete m_pcRobotState;
		if (m_strFsmConfiguration.compare("") != 0) {
			delete m_pcFsmBuilder;
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Init(TConfigurationNode& t_node) {
		// Parsing parameters
		try {
			GetNodeAttributeOrDefault(t_node, "fsm-config", m_strFsmConfiguration, m_strFsmConfiguration);
			GetNodeAttributeOrDefault(t_node, "evaluator-type", m_strEvaluatorType, m_strEvaluatorType);
			GetNodeAttributeOrDefault(t_node, "history", m_bMaintainHistory, m_bMaintainHistory);
			GetNodeAttributeOrDefault(t_node, "hist-folder", m_strHistoryFolder, m_strHistoryFolder);
			GetNodeAttributeOrDefault(t_node, "readable", m_bPrintReadableFsm, m_bPrintReadableFsm);
		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Error parsing <params>", ex);
		}

		m_unRobotID = atoi(GetId().substr(5, 6).c_str());
		m_pcRobotState->SetRobotIdentifier(m_unRobotID);

		/*
		 * If a FSM configuration is given as parameter of the experiment file, create a FSM from it
		 */
		if (m_strFsmConfiguration.compare("") != 0 && !m_bFiniteStateMachineGiven) {
			m_pcFsmBuilder = new AutoMoDeFsmBuilder();
			SetFiniteStateMachine(m_pcFsmBuilder->BuildFiniteStateMachine(m_strFsmConfiguration));
			if (m_bMaintainHistory) {
				m_pcFiniteStateMachine->SetHistoryFolder(m_strHistoryFolder);
				m_pcFiniteStateMachine->MaintainHistory();
			}
			if (m_bPrintReadableFsm) {
				std::cout << "Finite State Machine description: " << std::endl;
				std::cout << m_pcFiniteStateMachine->GetReadableFormat() << std::endl;
			}
		} else {
			LOGERR << "[WARNING] No finite state machine configuration found in .argos" << std::endl;
		}

		/*
		 * Create an evaluator according to its name and set the evaluation period; if the name is
		 * unknown, create a dummy evaluator
		 */
		SetEvaluator(AutoMoDeEvaluator::Build(m_strEvaluatorType));
		if (m_bFiniteStateMachineGiven) {
			m_pcEvaluator->SetEvaluationTime(m_pcFiniteStateMachine->GetEvaluationTime());
		}

		/*
		 *  Initializing sensors and actuators
		 */
		try {
			m_pcProximitySensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] sensor epuck_proximity not initialized " << std::endl;
		}
		try {
			m_pcLightSensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] sensor epuck_light not initialized " << std::endl;
		}
		try {
			m_pcGroundSensor = GetSensor<CCI_EPuckGroundSensor>("epuck_ground");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] sensor epuck_ground not initialized " << std::endl;
		}
		try {
			m_pcRabSensor = GetSensor<CCI_EPuckRangeAndBearingSensor>("epuck_range_and_bearing");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] sensor epuck_range_and_bearing not initialized " << std::endl;
		}
		try {
			m_pcCameraSensor = GetSensor<CCI_EPuckOmnidirectionalCameraSensor>("epuck_omnidirectional_camera");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] sensor epuck_omnidirectional_camera not initialized " << std::endl;
		}

		if (m_pcCameraSensor != NULL) {
			m_pcCameraSensor->Enable();
		}

		try {
			m_pcWheelsActuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] actuator epuck_wheels not initialized " << std::endl;
		}
		try {
			m_pcRabActuator = GetActuator<CCI_EPuckRangeAndBearingActuator>("epuck_range_and_bearing");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] actuator epuck_range_and_bearing not initialized " << std::endl;
		}
		try {
			m_pcLEDsActuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
		} catch (CARGoSException& ex) {
			LOGERR << "[WARNING] actuator epuck_rgb_leds not initialized " << std::endl;
		}

		/*
		 * Starts actuation.
		 */
		InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::ControlStep() {
		/*
		 * 1. Update RobotDAO
		 */
		if (m_pcRabSensor != NULL) {
			const CCI_EPuckRangeAndBearingSensor::TPackets& packets = m_pcRabSensor->GetPackets();
			//m_pcRobotState->SetNumberNeighbors(packets.size());
			m_pcRobotState->SetRangeAndBearingMessages(packets);
		}
		if (m_pcGroundSensor != NULL) {
			const CCI_EPuckGroundSensor::SReadings& readings = m_pcGroundSensor->GetReadings();
			m_pcRobotState->SetGroundInput(readings);
		}
		if (m_pcLightSensor != NULL) {
			const CCI_EPuckLightSensor::TReadings& readings = m_pcLightSensor->GetReadings();
			m_pcRobotState->SetLightInput(readings);
		}
		if (m_pcProximitySensor != NULL) {
			const CCI_EPuckProximitySensor::TReadings& readings = m_pcProximitySensor->GetReadings();
			m_pcRobotState->SetProximityInput(readings);
		}
		if (m_pcCameraSensor != NULL) {
			const CCI_EPuckOmnidirectionalCameraSensor::SReadings& readings = m_pcCameraSensor->GetReadings();
			m_pcRobotState->SetCameraInput(readings);
		}

		/*
		 * 2. Execute step of FSM
		 */
		m_pcFiniteStateMachine->ControlStep();

		/*
		 * 3. Update Actuators
		 */
		if (m_pcWheelsActuator != NULL) {
			m_pcWheelsActuator->SetLinearVelocity(m_pcRobotState->GetLeftWheelVelocity(),m_pcRobotState->GetRightWheelVelocity());
		}
		if (m_pcLEDsActuator != NULL) {
			m_pcLEDsActuator->SetColors(m_pcRobotState->GetLEDsColor());
			//m_pcLEDsActuator->SetColor(2,m_pcRobotState->GetLEDsColor());
		}
		if (m_pcRabActuator != NULL) {
			const UInt8 message = m_pcRobotState->GetMessageToSend();
			m_pcRabActuator->SetData(&message);
		}

		/*
		 * 4. Update variables and sensors
		 */
		if (m_pcRabSensor != NULL) {
			m_pcRabSensor->ClearPackets();
		}
		m_unTimeStep++;

		/*
		 * 5. Evaluate the robot performance and trigger the adaptation
		 */
		m_pcEvaluator->ControlStep();
		m_pcFiniteStateMachine->Adapt(m_pcEvaluator->CurrentPerformance());
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Destroy() {
		delete m_pcEvaluator;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::Reset() {
		m_pcFiniteStateMachine->Reset();
		m_pcEvaluator->Reset();
		m_pcRobotState->Reset();
		// Restart actuation.
		InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_finite_state_machine) {
		m_pcFiniteStateMachine = pc_finite_state_machine;
		m_pcFiniteStateMachine->SetRobotDAO(m_pcRobotState);
		m_pcFiniteStateMachine->Init();
		m_bFiniteStateMachineGiven = true;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetEvaluator(AutoMoDeEvaluator* pcEvaluator) {
		m_pcEvaluator = pcEvaluator;
		m_pcEvaluator->SetRobotDAO(m_pcRobotState);
		m_pcEvaluator->Init();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::SetHistoryFlag(bool b_history_flag) {
		if (b_history_flag) {
			m_pcFiniteStateMachine->MaintainHistory();
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeController::InitializeActuation() {
		/*
		 * Constantly send range-and-bearing messages containing the robot integer identifier.
		 */
		if (m_pcRabActuator != NULL) {
			UInt8 data[4];
			data[0] = m_unRobotID;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
			m_pcRabActuator->SetData(data);
		}
	}

	REGISTER_CONTROLLER(AutoMoDeController, "automode_controller");
}
