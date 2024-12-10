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

        // sort the messages according to sender and message ID
        auto Comparator = [](auto a, auto b){
            return a->Data[0] != b->Data[0] // check the sender of the two messages...
            ? a->Data[0] < b->Data[0]       // ...if it differs, use it to compare the messages
            : a->Data[1] < b->Data[1];      // ...if it coincides, compare according to message ID
        };
        std::sort(messages.begin(), messages.end(), Comparator);

        // remove messages with the same sender: we want only the last message
        auto SameSource = [this](auto a, auto b){ return a->Data[0] == b->Data[0]; };
        auto end = std::unique(messages.begin(), messages.end(), SameSource);
        messages.erase(end, messages.end());

        // remove message that were already evaluated (same or smaller message ID from same sender)
        auto AlreadyConsidered = [this](auto o){
            return un_mMessageIDs.find(o->Data[0]) != un_mMessageIDs.end()  // if the map does not
                                                                            // contain the ID then
                                                                            // the message has not
                                                                            // been evaluated
                                                                            // before...
                && un_mMessageIDs[o->Data[0]] >= o->Data[1];                // if there is track of
                                                                            // a message from the
                                                                            // same sender, check
                                                                            // if the message is
                                                                            // newer.
        };
        end = std::remove_if(messages.begin(), messages.end(), AlreadyConsidered);
        messages.erase(end, messages.end());

        // count the new reward messages and add them to the performance
        m_fCurrentPerformance = std::distance(messages.begin(), messages.end());
        m_fCumulativePerformance += m_fCurrentPerformance;

        // update the message IDs
        for (auto o : messages) {
            un_mMessageIDs[o->Data[0]] = o->Data[1]; // TODO overflow at 256
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
