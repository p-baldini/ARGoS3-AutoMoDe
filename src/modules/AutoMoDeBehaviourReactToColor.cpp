/**
 * @file <src/modules/AutoMoDeBehaviourReactToColor.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviourReactToColor.h"

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor::AutoMoDeBehaviourReactToColor() {
        m_strLabel = "ReactToColor";
    }

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor::AutoMoDeBehaviourReactToColor(AutoMoDeBehaviourReactToColor* pc_behaviour) {
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

    AutoMoDeBehaviourReactToColor::~AutoMoDeBehaviourReactToColor() {}

    /****************************************/
    /****************************************/

    AutoMoDeBehaviourReactToColor* AutoMoDeBehaviourReactToColor::Clone() {
        return new AutoMoDeBehaviourReactToColor(this);   // todo: check without *
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::ControlStep() {
        CCI_EPuckOmnidirectionalCameraSensor::SReadings sReadings = m_pcRobotDAO->GetCameraInput();
        CCI_EPuckOmnidirectionalCameraSensor::TBlobList::iterator it;
        CVector2 sColVectorSum(0,CRadians::ZERO);
        CVector2 sProxVectorSum(0,CRadians::ZERO);
        CVector2 sResultVector(0,CRadians::ZERO);

        for (it = sReadings.BlobList.begin(); it != sReadings.BlobList.end(); it++) {
            if ((*it)->Color == m_cColorReceiverParameter && (*it)->Distance >= 6.0) {
                sColVectorSum += CVector2(1 / (((*it)->Distance)+1), (*it)->Angle);
            }
            // TODO Check sColVectorSum function
        }

        sProxVectorSum = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);

        // these lines of code are taken directly from "go to color" and "go away color"
        std::cout << "aaa " << (m_iReactionType == APPROACH) << " " << (m_iReactionType == FLEE) << "\n";
        std::flush(std::cout);
        if (m_iReactionType == APPROACH) {
            sResultVector = CVector2(m_unReactionParameter, sColVectorSum.Angle().SignedNormalize()) - 6*sProxVectorSum;
        }
        else
        if (sColVectorSum.Length() != 0) {
        	sResultVector = -CVector2(m_unReactionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;
        }
        else {
        	sResultVector = CVector2(m_unReactionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;
        }

        m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));
        m_pcRobotDAO->SetLEDsColor(m_cColorEmitterParameter);

        m_bLocked = false;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Init() {
        m_iReactionType.Init(FindParameter<Real>("crt"));
        m_unReactionParameter.Init(FindParameter<Real>("vel"));
        m_cColorEmitterParameter = GetColorParameter(FindParameter<Real>("cle"), true);
        m_cColorReceiverParameter = GetColorParameter(FindParameter<Real>("clr"), true);
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Reset() {
        m_bOperational = false;
        ResumeStep();
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::ResumeStep() {
        m_bOperational = true;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeBehaviourReactToColor::Adapt(Real reward) {
        m_iReactionType.Adapt(reward);
        m_unReactionParameter.Adapt(reward);
    }
}
