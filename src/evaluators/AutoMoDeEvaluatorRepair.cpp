/**
 * @file <src/modules/AutoMoDeEvaluatorRepair.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
#include "AutoMoDeEvaluatorRepair.hpp"

#include <algorithm>

namespace argos {

    /****************************************/
    /****************************************/

    AutoMoDeEvaluatorRepair::~AutoMoDeEvaluatorRepair() {
        LOG << "cumulative performance: " << CumulativePerformance() << std::endl;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorRepair::Init() {
        AutoMoDeEvaluator::Init();
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorRepair::Reset() {
        AutoMoDeEvaluator::Reset();
        m_fCurrentPerformance = 0;
        m_fCumulativePerformance = 0;
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorRepair::ControlStep() {
        AutoMoDeEvaluator::ControlStep();

        // get the messages from the range and bearing
        std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> messages =
            m_pcRobotDAO->GetRangeAndBearingMessages();

        // create and fill a vector where to save sender and content of a message
        std::vector<std::pair<UInt8, UInt32>> senderAndContent;
        for (auto m : messages) {
            auto sender =  *((UInt32*)m->Data) >> 24;
            auto content = *((UInt32*)m->Data) & 0x00ffffff;
            senderAndContent.push_back(std::pair<UInt8, UInt32>(sender, content));
        }

        // sort the messages according to sender and message ID (sender has the precedence)
        auto Comparator = [](auto a, auto b) {
            return a.first != b.first ? a.first < b.first : a.second < b.second;
        };
        std::sort(senderAndContent.begin(), senderAndContent.end(), Comparator);

        // remove messages with the same sender: we want only the last message
        auto SameSource = [this](auto a, auto b){ return a.first == b.first; };
        auto end = std::unique(senderAndContent.begin(), senderAndContent.end(), SameSource);
        senderAndContent.erase(end, senderAndContent.end());

        // remove message that were already evaluated (same or smaller message ID from same sender)
        auto AlreadyConsidered = [this](auto o){
            return un_mMessageIDs.find(o.first) != un_mMessageIDs.end() // if the map does not
                                                                        // contain the ID then the
                                                                        // message has not been
                                                                        // evaluated before...
                && un_mMessageIDs[o.first] >= o.second;                 // if there is track of a
                                                                        // message from the same
                                                                        // sender, check if the
                                                                        // message is newer.
        };
        end = std::remove_if(senderAndContent.begin(), senderAndContent.end(), AlreadyConsidered);
        senderAndContent.erase(end, senderAndContent.end());

        // std::cout << "aaa " << std::distance(messages.begin(), messages.end()) << std::endl;

        // count the new reward messages and add them to the performance
        m_fCurrentPerformance = std::distance(senderAndContent.begin(), senderAndContent.end());
        m_fCumulativePerformance += m_fCurrentPerformance;

        // update the message IDs
        for (auto o : senderAndContent) {
            un_mMessageIDs[o.first] = o.second;
        }
    }

    /****************************************/
    /****************************************/

    void AutoMoDeEvaluatorRepair::NewEvaluation() {
        AutoMoDeEvaluator::NewEvaluation();
        m_fCurrentPerformance = 0;
    }

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluatorRepair::CurrentPerformance() {
        return m_fCurrentPerformance;
    }

    /****************************************/
    /****************************************/

    Real AutoMoDeEvaluatorRepair::CumulativePerformance() {
        return m_fCumulativePerformance;
    }
}
