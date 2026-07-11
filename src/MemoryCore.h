#ifndef MEMORYCORE_MEMORYCORE_H
#define MEMORYCORE_MEMORYCORE_H

#include <Arduino.h>
#include <SPI.h>

#include "SPIBus.h"
#include "FlashDevice.h"
#include "FlashConfig.h"

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

    // Read
    bool read(uint32_t address, void *buffer, uint32_t length);

    // Write
    bool write(uint32_t address, const void *data, uint32_t length);

    // Update
    bool update(uint32_t address, const void *data, uint32_t length);

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

    template <typename T>
    bool updateObject(uint32_t address, T &object)
    {
        return update(address, &object, sizeof(T));
    }

    // Erase
    bool eraseSector(uint32_t sector);

    bool eraseBlock32K(uint32_t block);

    bool eraseBlock64K(uint32_t block);

    bool eraseChip();

    // Status
    bool busy();
    uint8_t _sectorBuffer[W25Q_FLASH_SECTOR_SIZE];
    bool validRange(uint32_t address, uint32_t length);

    bool requiresErase(const uint8_t *oldData, const uint8_t *newData, uint32_t length);
    FlashDevice _flash;

private:
    // HardwareSerial &_serial;
    SPIBus _spi;

    JEDECID _jedec;
};

#endif
