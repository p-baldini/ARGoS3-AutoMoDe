/**
 * @file <src/modules/AutoMoDeBehaviour.cpp>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeBehaviour.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviour::AutoMoDeBehaviour() { }

	/****************************************/
	/****************************************/

	AutoMoDeBehaviour::AutoMoDeBehaviour(const AutoMoDeBehaviour* other) {
		m_strLabel = other->GetLabel();
		m_bLocked = other->IsLocked();
		m_bOperational = other->IsOperational();
		m_unIndex = other->GetIndex();
		m_unIdentifier = other->GetIdentifier();
		m_Parameters = other->m_Parameters;
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviour::~AutoMoDeBehaviour() { }

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsLocked() const {
		return m_bLocked;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetParameters(AutoMoDeParameters* parameters) {
		m_Parameters = parameters;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIndex(const UInt32& un_index) {
		m_unIndex = un_index;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeBehaviour::GetIndex() const {
		return m_unIndex;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIdentifier(const UInt32& un_id) {
		m_unIdentifier = un_id;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeBehaviour::GetIdentifier() const {
		return m_unIdentifier;
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviour::ComputeWheelsVelocityFromVector(CVector2 c_vector_to_follow) {
		Real fLeftVelocity = 0;
		Real fRightVelocity = 0;
		CRange<CRadians> cLeftHemisphere(CRadians::ZERO, CRadians::PI);
		CRange<CRadians> cRightHemisphere(CRadians::PI, CRadians::TWO_PI);
		CRadians cNormalizedVectorToFollow = c_vector_to_follow.Angle().UnsignedNormalize();
		// Compute relative wheel velocity
		// if (c_vector_to_follow.GetX() != 0 || c_vector_to_follow.GetY() != 0) {
		// 	if (cLeftHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
		// 		fRightVelocity = 1;
		// 		fLeftVelocity = Max<Real>(-0.5f, Cos(cNormalizedVectorToFollow));
		// 	} else {
		// 		fRightVelocity = Max<Real>(-0.5f, Cos(cNormalizedVectorToFollow));
		// 		fLeftVelocity = 1;
		// 	}
		// }
		if (c_vector_to_follow.GetX() != 0 || c_vector_to_follow.GetY() != 0) {
			if (cLeftHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
				fRightVelocity = 1;
				fLeftVelocity = Cos(cNormalizedVectorToFollow);
			} else {
				fRightVelocity = Cos(cNormalizedVectorToFollow);
				fLeftVelocity = 1;
			}
		}

		// Transform relative velocity according to max velocity allowed
		Real fVelocityFactor = m_pcRobotDAO->GetMaxVelocity();
		fVelocityFactor /= Max<Real>(std::abs(fRightVelocity), std::abs(fLeftVelocity));
		CVector2 cWheelsVelocity = CVector2(
			fVelocityFactor * fLeftVelocity,
			fVelocityFactor * fRightVelocity
		);

		return cWheelsVelocity;
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviour::SumProximityReadings(CCI_EPuckProximitySensor::TReadings s_prox) {
		CVector2 cSum(0, 0);
		for (UInt8 i = 0; i < s_prox.size(); i++) {
			cSum += CVector2(s_prox[i].Value, s_prox[i].Angle);
		}
		return cSum;
	}

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsOperational() const {
		return m_bOperational;
	}

	/****************************************/
	/****************************************/

	const std::string& AutoMoDeBehaviour::GetLabel() const {
		return m_strLabel;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetRobotDAO(EpuckDAO* pc_robot_dao) {
		m_pcRobotDAO = pc_robot_dao;
	}

    /****************************************/
    /****************************************/
    // Return the color parameter
    CColor AutoMoDeBehaviour::GetColorParameter(const UInt32& un_value, const bool& b_emitter) {

        CColor cColorParameter;

        //********************************************************
        // HARD CODED true for real robots, false for simulation
        // TODO Change for parameter in xml

        bool b_real_robot = true;

        //********************************************************

        if (b_real_robot && b_emitter){
            switch(un_value){
            case 0:
                cColorParameter = CColor::BLACK;
                break;
            case 1:
                cColorParameter = CColor::GREEN;
                break;
            case 2:
                cColorParameter = CColor::BLUE;
                break;
            case 3:
                cColorParameter = CColor::RED;
                break;
            case 4:
                cColorParameter = CColor(250,80,0);
                break;
            case 5:
                cColorParameter = CColor(150,0,60);
                break;
            case 6:
                cColorParameter = CColor(0,200,50);
                break;
            default:
                cColorParameter = CColor::BLACK;
            }
        }
        else {
            switch(un_value){
            case 0:
                cColorParameter = CColor::BLACK;
                break;
            case 1:
                cColorParameter = CColor::GREEN;
                break;
            case 2:
                cColorParameter = CColor::BLUE;
                break;
            case 3:
                cColorParameter = CColor::RED;
                break;
            case 4:
                cColorParameter = CColor::YELLOW;
                break;
            case 5:
                cColorParameter = CColor::MAGENTA;
                break;
            case 6:
                cColorParameter = CColor::CYAN;
                break;
            default:
                cColorParameter = CColor::BLACK;
            }
        }

        return cColorParameter;
    }
}
