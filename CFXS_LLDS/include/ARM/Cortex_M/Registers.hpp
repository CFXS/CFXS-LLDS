#pragma once

namespace CFXS::LLDS::ARM::Cortex_M {

    enum class Register : uint8_t {
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

    static inline Register IndexToCoreRegister(uint32_t index) {
        CFXS_ASSERT(index <= 15, "Invalid core register: R%u", index); // Index including SP/LR/PC
        return static_cast<Register>(static_cast<std::underlying_type<Register>::type>(Register::Rn) + index);
    }

    template<uint32_t INDEX>
    static inline Register IndexToCoreRegister() {
        static_assert(INDEX <= 15, "Invalid core register"); // Index including SP/LR/PC
        return static_cast<Register>(static_cast<std::underlying_type<Register>::type>(Register::Rn) + INDEX);
    }

    static inline Register IndexToFloatingPointRegister(uint32_t index) {
        CFXS_ASSERT(index <= 31, "Invalid FP register: S%u", index);
        return static_cast<Register>(static_cast<std::underlying_type<Register>::type>(Register::Sn) + index);
    }

    template<uint32_t INDEX>
    static inline Register IndexToFloatingPointRegister() {
        static_assert(INDEX <= 31, "Invalid FP register");
        return static_cast<Register>(static_cast<std::underlying_type<Register>::type>(Register::Sn) + INDEX);
    }

} // namespace CFXS::LLDS::ARM::Cortex_M
