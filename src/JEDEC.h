#ifndef MEMORYCORE_JEDEC_H
#define MEMORYCORE_JEDEC_H

#include <Arduino.h>

//=============================================================================
// JEDEC Manufacturer IDs
//=============================================================================

namespace Manufacturer
{
    constexpr uint8_t Winbond = 0xEF;
}

//=============================================================================
// Memory Type
//=============================================================================

namespace MemoryType
{
    constexpr uint8_t SerialNORFlash = 0x40;
}

//=============================================================================
// Capacity IDs
//=============================================================================

namespace Capacity
{
    constexpr uint8_t W25Q16 = 0x15;  // 16 Mbit (2 MB)
    constexpr uint8_t W25Q32 = 0x16;  // 32 Mbit (4 MB)
    constexpr uint8_t W25Q64 = 0x17;  // 64 Mbit (8 MB)
    constexpr uint8_t W25Q128 = 0x18; // 128 Mbit (16 MB)
    constexpr uint8_t W25Q256 = 0x19; // 256 Mbit (32 MB)
}

//=============================================================================
// JEDEC Identification
//=============================================================================

struct JEDECID
{
    uint8_t manufacturer;
    uint8_t memoryType;
    uint8_t capacity;
};

//=============================================================================
// Flash Geometry
//=============================================================================

struct FlashGeometry
{
    uint32_t capacityBytes;

    uint32_t pageSize;

    uint32_t sectorSize;

    uint32_t block32Size;

    uint32_t block64Size;

    uint32_t pageCount;

    uint32_t sectorCount;

    uint32_t block32Count;

    uint32_t block64Count;
};

//=============================================================================
// Utility
//=============================================================================

inline bool isWinbond(const JEDECID &id)
{
    return id.manufacturer == Manufacturer::Winbond;
}

inline uint32_t capacityBytes(uint8_t capacityCode)
{
    switch (capacityCode)
    {
    case Capacity::W25Q16:
        return 2UL * 1024UL * 1024UL;

    case Capacity::W25Q32:
        return 4UL * 1024UL * 1024UL;

    case Capacity::W25Q64:
        return 8UL * 1024UL * 1024UL;

    case Capacity::W25Q128:
        return 16UL * 1024UL * 1024UL;

    case Capacity::W25Q256:
        return 32UL * 1024UL * 1024UL;

    default:
        return 0;
    }
}

#endif // MEMORYCORE_JEDEC_H
