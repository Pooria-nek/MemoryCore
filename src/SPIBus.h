#ifndef MEMORYCORE_SPIBUS_H
#define MEMORYCORE_SPIBUS_H

#include <Arduino.h>
#include <SPI.h>

#include "FlashConfig.h"

class SPIBus
{
public:
    SPIBus(
        SPIClass &spi,
        uint8_t chipSelectPin);

    void begin();

    void beginTransaction();

    void endTransaction();

    uint8_t transfer(uint8_t data);

    void transfer(
        const uint8_t *txBuffer,
        uint8_t *rxBuffer,
        size_t length);

    void write(
        const uint8_t *data,
        size_t length);

    void read(
        uint8_t *data,
        size_t length,
        uint8_t filler = 0xFF);

private:
    SPIClass &_spi;

    uint8_t _csPin;

    SPISettings _settings;
};

#endif // MEMORYCORE_SPIBUS_H
