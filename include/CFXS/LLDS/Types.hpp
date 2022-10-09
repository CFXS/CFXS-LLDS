// [CFXS] //
#pragma once
#include <CFXS/Base/Utility.hpp>

namespace CFXS {
    namespace LLDS {

        // Status of some kind of protocol operation (hardware or software level)
        enum class ProtocolStatus : uint32_t {
            // OK/WAIT/FAULT/NO_RESPONSE are the same values as defined in ADIv5 to avoid enum conversion ifs
            // OK and ERROR(FAULT) values are bit-reversed (ACK is sent in reverse order)
            // Easier to swap definition instead of dynamically reordering after read
            OK          = 0b001,       // Response good
            WAIT        = 0b010,       // Try again later
            FAULT       = 0b100,       // Something wrong
            ERROR       = FAULT,       // Alias for FAULT
            NO_RESPONSE = 0b111,       // No physical response
            BAD_DATA,                  // Bad parity or other type of data error
            TIMEOUT,                   // Not the same as no response - did not do something in time
            UNSUPPORTED_DEVICE,        // Device not supported :(
            SWD_INVALID_ACK_1 = 0b110, // Not a valid SWD ACK Code
            SWD_INVALID_ACK_2 = 0b011, // Not a valid SWD ACK Code
        };
        CFXS_ENUM_OPERATORS(ProtocolStatus)

    } // namespace LLDS

    static const char* ToString(LLDS::ProtocolStatus stat) {
        switch (stat) {
            case LLDS::ProtocolStatus::OK: return "OK";
            case LLDS::ProtocolStatus::WAIT: return "WAIT";
            case LLDS::ProtocolStatus::ERROR: return "ERROR";
            case LLDS::ProtocolStatus::NO_RESPONSE: return "NO_RESPONSE";
            case LLDS::ProtocolStatus::BAD_DATA: return "BAD_DATA";
            case LLDS::ProtocolStatus::TIMEOUT: return "TIMEOUT";
            default: return "???";
        }
    }

} // namespace CFXS
