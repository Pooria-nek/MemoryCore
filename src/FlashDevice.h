#ifndef MEMORYCORE_FLASHDEVICE_H
#define MEMORYCORE_FLASHDEVICE_H

#include <Arduino.h>

#include "SPIBus.h"
#include "JEDEC.h"

namespace MC
{

    class FlashDevice
    {
    public:
        explicit FlashDevice(SPIBus &spi);

        bool begin();

        //-------------------------------------------------------------------------
        // Identification
        //-------------------------------------------------------------------------

        JEDECID readJEDECID();

        uint64_t readUniqueID();

        const FlashGeometry &geometry() const;

        //-------------------------------------------------------------------------
        // Status
        //-------------------------------------------------------------------------

        uint8_t readStatus1();

        uint8_t readStatus2();

        uint8_t readStatus3();

        bool busy();

        void waitWhileBusy();

        //-------------------------------------------------------------------------
        // Power
        //-------------------------------------------------------------------------

        void reset();

        void powerDown();

        void wakeUp();

        //-------------------------------------------------------------------------
        // Write Control
        //-------------------------------------------------------------------------

        void writeEnable();

        void writeDisable();

        //-------------------------------------------------------------------------
        // Read / Write
        //-------------------------------------------------------------------------

        void read(
            uint32_t address,
            void *buffer,
            uint32_t length);

        void pageProgram(
            uint32_t address,
            const void *data,
            uint16_t length);

        //-------------------------------------------------------------------------
        // Erase
        //-------------------------------------------------------------------------

        void eraseSector(uint32_t address);

        void eraseBlock32K(uint32_t address);

        void eraseBlock64K(uint32_t address);

        void eraseChip();

    private:
        SPIBus &_spi;

        FlashGeometry _geometry;

        void sendAddress(uint32_t address);

        void detectGeometry(const JEDECID &id);
    };

}

#endif
