#ifndef MEMORYCORE_COMMANDS_H
#define MEMORYCORE_COMMANDS_H

#include <Arduino.h>

namespace MemoryCore
{
namespace Command
{
    //-------------------------------------------------------------------------
    // Identification
    //-------------------------------------------------------------------------

    constexpr uint8_t ReadJEDECID      = 0x9F;
    constexpr uint8_t ReadUniqueID     = 0x4B;
    constexpr uint8_t ReadManufacturer = 0x90;

    //-------------------------------------------------------------------------
    // Read Operations
    //-------------------------------------------------------------------------

    constexpr uint8_t ReadData         = 0x03;
    constexpr uint8_t FastRead         = 0x0B;

    //-------------------------------------------------------------------------
    // Program Operations
    //-------------------------------------------------------------------------

    constexpr uint8_t WriteEnable      = 0x06;
    constexpr uint8_t WriteDisable     = 0x04;
    constexpr uint8_t PageProgram      = 0x02;

    //-------------------------------------------------------------------------
    // Erase Operations
    //-------------------------------------------------------------------------

    constexpr uint8_t SectorErase      = 0x20;
    constexpr uint8_t BlockErase32K    = 0x52;
    constexpr uint8_t BlockErase64K    = 0xD8;
    constexpr uint8_t ChipErase        = 0xC7;

    // Alternative chip erase opcode
    constexpr uint8_t ChipEraseAlt     = 0x60;

    //-------------------------------------------------------------------------
    // Status Registers
    //-------------------------------------------------------------------------

    constexpr uint8_t ReadStatus1      = 0x05;
    constexpr uint8_t ReadStatus2      = 0x35;
    constexpr uint8_t ReadStatus3      = 0x15;

    constexpr uint8_t WriteStatus      = 0x01;

    //-------------------------------------------------------------------------
    // Power Management
    //-------------------------------------------------------------------------

    constexpr uint8_t PowerDown        = 0xB9;
    constexpr uint8_t ReleasePowerDown = 0xAB;

    //-------------------------------------------------------------------------
    // Reset
    //-------------------------------------------------------------------------

    constexpr uint8_t EnableReset      = 0x66;
    constexpr uint8_t ResetDevice      = 0x99;

    //-------------------------------------------------------------------------
    // Miscellaneous
    //-------------------------------------------------------------------------

    constexpr uint8_t Enable4ByteAddr  = 0xB7;
    constexpr uint8_t Disable4ByteAddr = 0xE9;
}
}

#endif // MEMORYCORE_COMMANDS_H
