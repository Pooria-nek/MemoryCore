#ifndef MEMORYCORE_MEMORYCORE_H
#define MEMORYCORE_MEMORYCORE_H

#include <Arduino.h>
#include <SPI.h>

#include "SPIBus.h"
#include "FlashDevice.h"

namespace MC // memory core 
{

    class MemoryCore
    {
    public:
        MemoryCore(SPIClass &spi, uint8_t chipSelectPin);

        bool begin();

        // Information
        uint32_t capacity() const;
        uint32_t pageSize() const;
        uint32_t sectorSize() const;

        JEDECID jedecID();
        uint64_t uniqueID();

        // Read / Write
        bool read(
            uint32_t address,
            void *buffer,
            uint32_t length);

        bool write(
            uint32_t address,
            const void *data,
            uint32_t length);

        bool writeByte(
            uint32_t address,
            uint8_t value);

        uint8_t readByte(
            uint32_t address);

        template <typename T>
        bool writeObject(uint32_t address, const T &object)
        {
            return write(address, &object, sizeof(T));
        }

        template <typename T>
        bool readObject(uint32_t address, T &object)
        {
            return read(address, &object, sizeof(T));
        }

        // Erase
        bool eraseSector(uint32_t sector);

        bool eraseBlock32K(uint32_t block);

        bool eraseBlock64K(uint32_t block);

        bool eraseChip();

        // Status
        bool busy();

    private:
        SPIBus _spi;
        FlashDevice _flash;

        JEDECID _jedec;

        bool validRange(uint32_t address, uint32_t length);
    };

}

#endif
