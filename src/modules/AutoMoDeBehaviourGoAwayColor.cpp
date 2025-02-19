/**
 * @file <src/modules/AutoMoDeBehaviourRepulsion.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourGoAwayColor.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoAwayColor::AutoMoDeBehaviourGoAwayColor() {
		m_strLabel = "GoAwayColor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoAwayColor::AutoMoDeBehaviourGoAwayColor(
		AutoMoDeBehaviourGoAwayColor* pc_behaviour
	) : AutoMoDeBehaviour(pc_behaviour) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoAwayColor::~AutoMoDeBehaviourGoAwayColor() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoAwayColor* AutoMoDeBehaviourGoAwayColor::Clone() {
		return new AutoMoDeBehaviourGoAwayColor(this);
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviourGoAwayColor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "vel=" << m_unRepulsionParameter << std::endl;
		ss << "clr=" << m_cColorReceiverParameter << std::endl;
		ss << "cle=" << m_cColorEmitterParameter << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoAwayColor::ControlStep() {
		CCI_EPuckOmnidirectionalCameraSensor::SReadings sReadings = m_pcRobotDAO->GetCameraInput();
		CCI_EPuckOmnidirectionalCameraSensor::TBlobList::iterator it;
		CVector2 sColVectorSum(0,CRadians::ZERO);
		CVector2 sProxVectorSum(0,CRadians::ZERO);
		CVector2 sResultVector(0,CRadians::ZERO);

		for (it = sReadings.BlobList.begin(); it != sReadings.BlobList.end(); it++) {
			if ((*it)->Color == (CColor) m_cColorReceiverParameter  && (*it)->Distance >= 6.0) {
				sColVectorSum += CVector2(1 / (((*it)->Distance) + 1), (*it)->Angle);
			}
		}

		sProxVectorSum = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);

		if (sColVectorSum.Length() != 0)
			sResultVector = -CVector2(m_unRepulsionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;
		else
			sResultVector = CVector2(m_unRepulsionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));
		m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoAwayColor::Init() {
		m_unRepulsionParameter = m_Parameters->GetParameter<Real>("vel", m_unIndex);
		m_cColorReceiverParameter = m_Parameters->GetParameter<CColor>("clr", m_unIndex);
		m_cColorEmitterParameter = m_Parameters->GetParameter<CColor>("cle", m_unIndex, "0");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoAwayColor::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoAwayColor::ResumeStep() {
		m_bOperational = true;
	}
}
