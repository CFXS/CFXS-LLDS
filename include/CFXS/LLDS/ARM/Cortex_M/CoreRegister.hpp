#pragma once
#include <CFXS/Base/Debug.hpp>
#include <type_traits>

namespace CFXS::LLDS::ARM::Cortex_M {

    enum class CoreRegister : uint8_t {
        Rn    = 0,  // Core registers
        SP    = 13, // Current Stack Pointer
        LR    = 14, // Link Register
        PC    = 15, // Program Counter
        xPSR  = 16, // xPSR
        MSP   = 17, // Main stack pointer
        PSP   = 18, // Process stack pointer
        CFBP  = 20, // uint8_t[CONTROL, FAULTMASK, BASEPRI, PRIMASK]
        FPSCR = 33, // FP Status and Control Register
        Sn    = 64, // FP registers
    };

    static inline CoreRegister IndexToGeneralPurposeRegister(uint32_t index) {
        CFXS_ASSERT(index <= 15, "Invalid general purpose register: R%lu",
                    index); // Index including SP/LR/PC
        return static_cast<CoreRegister>(static_cast<std::underlying_type<CoreRegister>::type>(CoreRegister::Rn) + index);
    }

    template<uint32_t INDEX>
    static inline CoreRegister IndexToGeneralPurposeRegister() {
        static_assert(INDEX <= 15,
                      "Invalid general purpose register"); // Index including SP/LR/PC
        return static_cast<CoreRegister>(static_cast<std::underlying_type<CoreRegister>::type>(CoreRegister::Rn) + INDEX);
    }

    static inline CoreRegister IndexToFloatingPointRegister(uint32_t index) {
        CFXS_ASSERT(index <= 31, "Invalid FP register: S%lu", index);
        return static_cast<CoreRegister>(static_cast<std::underlying_type<CoreRegister>::type>(CoreRegister::Sn) + index);
    }

    template<uint32_t INDEX>
    static inline CoreRegister IndexToFloatingPointRegister() {
        static_assert(INDEX <= 31, "Invalid FP register");
        return static_cast<CoreRegister>(static_cast<std::underlying_type<CoreRegister>::type>(CoreRegister::Sn) + INDEX);
    }

} // namespace CFXS::LLDS::ARM::Cortex_M
