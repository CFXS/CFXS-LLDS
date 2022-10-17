#pragma once

namespace CFXS::LLDS::ADI {

    static constexpr bool COMMAND_AP    = true;
    static constexpr bool COMMAND_DP    = false;
    static constexpr bool COMMAND_READ  = true;
    static constexpr bool COMMAND_WRITE = false;

    enum class SWD_DP_Address : uint8_t { IDCODE = 0b00, ABORT = 0b00, CTRL_STAT = 0b10, RESEND = 0b01, SELECT = 0b01, RDBUFF = 0b11 };
    enum class SWD_MEM_AP_Address : uint8_t { CSW = 0b00, TAR = 0b10, DRW = 0b01, IDR = 0b11 };

#pragma pack(1)
    union SWD_Command_t {
        struct {
            bool Park : 1;
            bool Stop : 1;
            bool Parity : 1;
            uint8_t A : 2;
            bool RnW : 1;
            bool APnDP : 1;
            bool Start : 1;
        };
        uint8_t _val;
    };

    template<char RW, char AP_DP, auto A>
    struct SWD_Command {
        static_assert(RW == 'R' || RW == 'W', "Invalid Read/Write value [Valid: 'R' or 'W']");
        static_assert(AP_DP == 'A' || AP_DP == 'D', "Invalid AP/DP value [Valid: 'A' or 'D']");
        static constexpr uint8_t _address = static_cast<uint8_t>(A);
        static constexpr bool _parity =
            ((((RW == 'R') ? 1 : 0) + ((AP_DP == 'A') ? 1 : 0) + (((_address == 0b01 || _address == 0b10)) ? 1 : 0)) & 1) == 1;
        static constexpr uint8_t value = 0b10000001 | ((AP_DP == 'A') ? 0b01000000 : 0) | ((RW == 'R') ? 0b00100000 : 0) |
                                         ((_address & 0b11) << 3) | (_parity ? 0b00000100 : 0);
    };

    union IDCODE_t {
        struct {
            uint8_t _ : 1;
            uint16_t MANUFACTURER : 11;
            uint16_t PARTNO : 16;
            uint8_t Version : 4;
        };
        uint32_t _val;
    };
#pragma pack()

    namespace Command {

        namespace DP {
            static constexpr auto READ_IDCODE     = SWD_Command<'R', 'D', SWD_DP_Address::IDCODE>::value;
            static constexpr auto WRITE_ABORT     = SWD_Command<'W', 'D', SWD_DP_Address::ABORT>::value;
            static constexpr auto READ_CTRL_STAT  = SWD_Command<'R', 'D', SWD_DP_Address::CTRL_STAT>::value;
            static constexpr auto WRITE_CTRL_STAT = SWD_Command<'W', 'D', SWD_DP_Address::CTRL_STAT>::value;
            static constexpr auto READ_RESEND     = SWD_Command<'R', 'D', SWD_DP_Address::RESEND>::value;
            static constexpr auto WRITE_SELECT    = SWD_Command<'W', 'D', SWD_DP_Address::SELECT>::value;
            static constexpr auto READ_RDBUFF     = SWD_Command<'R', 'D', SWD_DP_Address::RDBUFF>::value;
        } // namespace DP

        namespace AP {
            static constexpr auto WRITE_CSW = SWD_Command<'W', 'A', SWD_MEM_AP_Address::CSW>::value;
            static constexpr auto WRITE_TAR = SWD_Command<'W', 'A', SWD_MEM_AP_Address::TAR>::value;
            static constexpr auto WRITE_DRW = SWD_Command<'W', 'A', SWD_MEM_AP_Address::DRW>::value;
            static constexpr auto READ_DRW  = SWD_Command<'R', 'A', SWD_MEM_AP_Address::DRW>::value;
            static constexpr auto READ_IDR  = SWD_Command<'R', 'A', SWD_MEM_AP_Address::IDR>::value;
        }; // namespace AP

    } // namespace Command

} // namespace CFXS::LLDS::ADI