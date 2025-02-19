/**
 * @file <src/modules/AutoMoDeBehaviourAttractionColor.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourGoToColor.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoToColor::AutoMoDeBehaviourGoToColor() {
		m_strLabel = "GoToColor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoToColor::AutoMoDeBehaviourGoToColor(
		AutoMoDeBehaviourGoToColor* pc_behaviour
	) : AutoMoDeBehaviour(pc_behaviour) {
		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoToColor::~AutoMoDeBehaviourGoToColor() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourGoToColor* AutoMoDeBehaviourGoToColor::Clone() {
		return new AutoMoDeBehaviourGoToColor(this);   // todo: check without *
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviourGoToColor::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel << std::endl;
		ss << "vel=" << m_unAttractionParameter << std::endl;
		ss << "clr=" << m_cColorReceiverParameter << std::endl;
		ss << "cle=" << m_cColorEmitterParameter << std::endl;
		return ss.str();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoToColor::ControlStep() {
		CCI_EPuckOmnidirectionalCameraSensor::SReadings sReadings = m_pcRobotDAO->GetCameraInput();
		CCI_EPuckOmnidirectionalCameraSensor::TBlobList::iterator it;
		CVector2 sColVectorSum(0,CRadians::ZERO);
		CVector2 sProxVectorSum(0,CRadians::ZERO);
		CVector2 sResultVector(0,CRadians::ZERO);

		for (it = sReadings.BlobList.begin(); it != sReadings.BlobList.end(); it++) {
			if ((*it)->Color == (CColor) m_cColorReceiverParameter && (*it)->Distance >= 6.0) {
				sColVectorSum += CVector2(1 / (((*it)->Distance)+1), (*it)->Angle);
			}
			// TODO Check sColVectorSum function
		}

		sProxVectorSum = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);

		sResultVector = CVector2(m_unAttractionParameter, sColVectorSum.Angle().SignedNormalize()) - 6*sProxVectorSum;

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));
		m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoToColor::Init() {
		m_unAttractionParameter = m_Parameters->GetParameter<Real>("vel", m_unIndex);
		m_cColorReceiverParameter = m_Parameters->GetParameter<CColor>("clr", m_unIndex);
		m_cColorEmitterParameter = m_Parameters->GetParameter<CColor>("cle", m_unIndex, "0");
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoToColor::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourGoToColor::ResumeStep() {
		m_bOperational = true;
	}
}
