#ifndef MEMORYCORE_FLASHSTATUS_H
#define MEMORYCORE_FLASHSTATUS_H

#include <Arduino.h>

namespace MemoryCore
{

//=============================================================================
// Status Register-1
//=============================================================================

namespace Status1
{
    constexpr uint8_t BUSY = (1 << 0);

    constexpr uint8_t WEL  = (1 << 1);

    constexpr uint8_t BP0  = (1 << 2);

    constexpr uint8_t BP1  = (1 << 3);

    constexpr uint8_t BP2  = (1 << 4);

    constexpr uint8_t TB   = (1 << 5);

    constexpr uint8_t SEC  = (1 << 6);

    constexpr uint8_t SRP0 = (1 << 7);
}

//=============================================================================
// Status Register-2
//=============================================================================

namespace Status2
{
    constexpr uint8_t SRP1 = (1 << 0);

    constexpr uint8_t QE   = (1 << 1);

    constexpr uint8_t LB1  = (1 << 3);

    constexpr uint8_t LB2  = (1 << 4);

    constexpr uint8_t LB3  = (1 << 5);

    constexpr uint8_t CMP  = (1 << 6);

    constexpr uint8_t SUS  = (1 << 7);
}

//=============================================================================
// Status Register-3
//=============================================================================

namespace Status3
{
    constexpr uint8_t WPS = (1 << 2);

    constexpr uint8_t ADS = (1 << 3);

    constexpr uint8_t ADP = (1 << 4);

    constexpr uint8_t HOLD_RST = (1 << 7);
}

//=============================================================================
// Helper Functions
//=============================================================================

inline bool isBusy(uint8_t status1)
{
    return status1 & Status1::BUSY;
}

inline bool writeEnabled(uint8_t status1)
{
    return status1 & Status1::WEL;
}

inline bool quadEnabled(uint8_t status2)
{
    return status2 & Status2::QE;
}

inline bool suspended(uint8_t status2)
{
    return status2 & Status2::SUS;
}

} // namespace MemoryCore

#endif // MEMORYCORE_FLASHSTATUS_H
