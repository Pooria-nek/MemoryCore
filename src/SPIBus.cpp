#include "SPIBus.h"

namespace MC
{

SPIBus::SPIBus(
    SPIClass& spi,
    uint8_t chipSelectPin)
    : _spi(spi),
      _csPin(chipSelectPin),
      _settings(
          MEMORYCORE_SPI_CLOCK,
          MEMORYCORE_SPI_BIT_ORDER,
          MEMORYCORE_SPI_MODE)
{
}

void SPIBus::begin()
{
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);

    _spi.begin();
}

void SPIBus::beginTransaction()
{
    _spi.beginTransaction(_settings);
    digitalWrite(_csPin, LOW);
}

void SPIBus::endTransaction()
{
    digitalWrite(_csPin, HIGH);
    _spi.endTransaction();
}

uint8_t SPIBus::transfer(uint8_t data)
{
    return _spi.transfer(data);
}

void SPIBus::transfer(
    const uint8_t* txBuffer,
    uint8_t* rxBuffer,
    size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        uint8_t tx = txBuffer ? txBuffer[i] : 0xFF;
        uint8_t rx = _spi.transfer(tx);

        if (rxBuffer)
        {
            rxBuffer[i] = rx;
        }
    }
}

void SPIBus::write(
    const uint8_t* data,
    size_t length)
{
    while (length--)
    {
        _spi.transfer(*data++);
    }
}

void SPIBus::read(
    uint8_t* data,
    size_t length,
    uint8_t filler)
{
    while (length--)
    {
        *data++ = _spi.transfer(filler);
    }
}

} // namespace MemoryCore
