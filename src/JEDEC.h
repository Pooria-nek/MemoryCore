#ifndef MEMORYCORE_JEDEC_H
#define MEMORYCORE_JEDEC_H

#include <Arduino.h>

namespace MemoryAdress
{

    constexpr uint32_t DEVICE_ADDRESS = 0x000010;     // 2 byte
    constexpr uint32_t DEVICE_TYPE = 0x000012;        // 2 byte
    constexpr uint32_t DEVICE_MAC_ADDRESS = 0x000014; // STM mac len

    constexpr uint32_t DEVICE_REMARK = 0x000020;
    constexpr uint32_t DEVICE_HARDWARE_VER = 0x000040;
    constexpr uint32_t DEVICE_SOFTWARE_VER = 0x000060;

    constexpr uint32_t CHANNEL_REMARK = 0x000080;
    constexpr uint32_t CHANNEL_REMARK_SIZE = 0x20;

    constexpr uint32_t channelRemark(uint8_t channel)
    {
        return (channel >= 1 && channel <= 32) ? CHANNEL_REMARK + (channel - 1) * CHANNEL_REMARK_SIZE : 0;
    }

    // base 1 to 32 same in all devices
    constexpr uint32_t setRemark(uint32_t remarkBase, uint8_t number)
    {
        return (number >= 1 && number <= 32) ? remarkBase + (number - 1) * remarkBase : 0;
    }

    // addreses are the same in all devices
    constexpr uint32_t channelAddress(uint32_t baseAddress, uint8_t channel)
    {
        return (channel >= 1 && channel <= 32) ? baseAddress + (channel - 1) : 0;
    }

    namespace Touch
    {
        // =====================================================
        // Sectors
        // =====================================================

        constexpr uint32_t SECTOR_INFO = 120;
        constexpr uint32_t SECTOR_FUNCTIONS = 121; // 8 secrot length
        constexpr uint32_t SECTOR_IMAGES = 400;    // 8 secrot length

        constexpr uint32_t SECTOR_ICONS = SECTOR_IMAGES + 8; // 8 secrot length => CONF=1

        // =====================================================
        // Touch Information
        // =====================================================

        constexpr uint32_t CHANNEL_MODE = 0x000480;
        constexpr uint32_t CHANNEL_STATUE = 0x0004A0;
        constexpr uint32_t CHANNEL_DIMMING = 0x0004C0;
        constexpr uint32_t CHANNEL_DIMMING_VALUE = 0x0004E0;

        // =====================================================
        // Channel Functions
        // =====================================================

        // Page valid(8) + return page(1) + return delay(1) + backlight dimm(1) + Button dimm(1)

        constexpr uint32_t CHANNEL_FUNCTION_BASE = 0x000000;
        constexpr uint32_t CHANNEL_FUNCTION_B_SIZE = 0x320;
        constexpr uint32_t CHANNEL_FUNCTION_F_SIZE = 0x08;

        constexpr uint32_t channelFunction(uint8_t button, uint8_t function)
        {
            if (button < 1 || button > 32)
            {
                return 0;
            }

            if (function < 1 || function > 100)
            {
                return 0;
            }
            return ((button - 1) * CHANNEL_FUNCTION_B_SIZE) + ((function - 1) * CHANNEL_FUNCTION_F_SIZE);
        }

        constexpr uint32_t PAGE_IMAGE_BASE = 0x000000;
        constexpr uint32_t PAGE_IMAGE_EACH_SIZE = 0x400;
        constexpr uint32_t PAGE_IMAGE_PACKET_SIZE = 0x10;
        constexpr uint32_t pageImage(uint8_t image, uint8_t packet)
        {
            // image = image;
            if (image < 0 || image > 7)
            {
                return 0;
            }
            if (packet < 0 || packet > 63)
            {
                return 0;
            }

            return PAGE_IMAGE_BASE + ((image)*PAGE_IMAGE_EACH_SIZE) + ((packet)*PAGE_IMAGE_PACKET_SIZE);
        }

        constexpr uint32_t PAGE_VALID_BASE = 0x000500;   // 8 LEN
        constexpr uint32_t PAGE_SLEEP_TIME = 0x000508;   // 1 LEN
        constexpr uint32_t PAGE_SLEEP_LEVEL = 0x000509;  // 1 LEN
        constexpr uint32_t PAGE_RETURN_PAGE = 0x00050A;  // 1 LEN
        constexpr uint32_t PAGE_RETURN_DELAY = 0x00050B; // 1 LEN
        // constexpr uint32_t PAGE_UNKNOWN = 0x00050C;
        constexpr uint32_t PAGE_WAKE_TRIG = 0x00050D; // 1 LEN

        constexpr uint32_t PROX_FLAG = 0x000510;       // 1 LEN
        constexpr uint32_t MIN_DIMM = 0x000511;        // 1 LEN
        constexpr uint32_t SHOW_TEMP = 0x000512;       // 1 LEN
        constexpr uint32_t LONG_PRESS_TIME = 0x000513; // 1 LEN
        constexpr uint32_t SHOW_TIME_DATE = 0x000514;  // 1 LEN
        // constexpr uint32_t PAGE_UNKNOWN = 0x000515;
        constexpr uint32_t FONT_SIZE = 0x000516;   // 1 LEN
        constexpr uint32_t TEMP_SOURCE = 0x000517; // 1 LEN

        constexpr uint32_t PAGE_LCD_DIMM = 0x000518;    // 1 LEN
        constexpr uint32_t PAGE_BUTTON_DIMM = 0x000519; // 1 LEN

        constexpr uint32_t TEMP_CALIBRATE = 0x00051A; // 1 LEN

        //////////////////////////////////////////////////////////////////

        constexpr uint32_t HVAC_0 = 0x000540;
        constexpr uint32_t HVAC_1 = 0x0005A0;
        constexpr uint32_t HVAC_2 = 0x000600;
        constexpr uint32_t HVAC_3 = 0x000660;
        constexpr uint32_t HVAC_4 = 0x0006C0;
        constexpr uint32_t HVAC_5 = 0x000720;
        constexpr uint32_t HVAC_6 = 0x000780;
        constexpr uint32_t HVAC_7 = 0x0007E0;

        static constexpr uint32_t HVAC_ADDRESSES[8] =
            {
                MemoryAdress::Touch::HVAC_0,
                MemoryAdress::Touch::HVAC_1,
                MemoryAdress::Touch::HVAC_2,
                MemoryAdress::Touch::HVAC_3,
                MemoryAdress::Touch::HVAC_4,
                MemoryAdress::Touch::HVAC_5,
                MemoryAdress::Touch::HVAC_6,
                MemoryAdress::Touch::HVAC_7};

        // 64x32, 1-bit = 256 bytes = 0x100

        constexpr uint32_t IMAGE_0 = 0x000000;
        constexpr uint32_t IMAGE_1 = 0x0000F0;
        constexpr uint32_t IMAGE_2 = 0x0001E0;
        constexpr uint32_t IMAGE_3 = 0x0002D0;
        constexpr uint32_t IMAGE_4 = 0x000400;
        constexpr uint32_t IMAGE_5 = 0x0004F0;
        constexpr uint32_t IMAGE_6 = 0x0005E0;
        constexpr uint32_t IMAGE_7 = 0x0006D0;

        static constexpr uint32_t HVAC_IMAGE[8] =
            {
                MemoryAdress::Touch::IMAGE_0,
                MemoryAdress::Touch::IMAGE_1,
                MemoryAdress::Touch::IMAGE_2,
                MemoryAdress::Touch::IMAGE_3,
                MemoryAdress::Touch::IMAGE_4,
                MemoryAdress::Touch::IMAGE_5,
                MemoryAdress::Touch::IMAGE_6,
                MemoryAdress::Touch::IMAGE_7};

        //////////////////////////////////////////////////////////////////

        constexpr uint32_t FHEAT_0 = 0x000540;
        constexpr uint32_t FHEAT_1 = 0x0005A0;
        constexpr uint32_t FHEAT_2 = 0x000600;
        constexpr uint32_t FHEAT_3 = 0x000660;

        static constexpr uint32_t FHEAT_ADDRESSES[4] =
            {
                MemoryAdress::Touch::FHEAT_0,
                MemoryAdress::Touch::FHEAT_1,
                MemoryAdress::Touch::FHEAT_2,
                MemoryAdress::Touch::FHEAT_3};

        // 64x32, 1-bit = 256 bytes = 0x100

        constexpr uint32_t FIMAGE_0 = 0x000800;
        constexpr uint32_t FIMAGE_1 = 0x0008F0;
        constexpr uint32_t FIMAGE_2 = 0x0009E0;
        constexpr uint32_t FIMAGE_3 = 0x000AD0;

        static constexpr uint32_t FHEAT_IMAGE[4] =
            {
                MemoryAdress::Touch::FIMAGE_0,
                MemoryAdress::Touch::FIMAGE_1,
                MemoryAdress::Touch::FIMAGE_2,
                MemoryAdress::Touch::FIMAGE_3};

    } // namespace Touch

    // namespace Relay
    // {
    //     // =====================================================
    //     // Sectors
    //     // =====================================================

    //     constexpr uint32_t SECTOR_DEVICE_INFO = 60;

    //     //////////////////////////////////////////////////////////////////

    //     constexpr uint32_t CHANNEL_ENABLE = 0x000380;
    //     constexpr uint32_t CHANNEL_ONDELAY = 0x0003A0;
    //     constexpr uint32_t CHANNEL_ONPROTECT = 0x0003C0;
    //             constexpr uint32_t CHANNEL_ZONE = 0x0003E0;

    //     // for values that has 1 byte per channel
    //     constexpr uint32_t channelAddress(uint32_t baseAddress, uint8_t channel)
    //     {
    //         return (channel >= 1 && channel <= 32) ? baseAddress + (channel - 1) : 0;
    //     }

    //     constexpr uint32_t CHANNEL_ZONE = 0x0003E0;
    //     // constexpr uint32_t ZONE_SCENE_POWERON_EN = 0x000400;
    //     // constexpr uint32_t ZONE_SCENE_POWERON_NUM = 0x000420;

    //     // constexpr uint32_t ZONE_REMARK = 0x000440;
    //     // constexpr uint32_t ZONE_REMARK_SIZE = 0x20;

    //     // // constexpr uint32_t SCENE_REMARK = 0x000440;
    //     // constexpr uint32_t SCENE_REMARK_SIZE = 0x20;

    // } // namespace Relay

    namespace Input
    {

    } // namespace Input

} // namespace memoryAdress

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
