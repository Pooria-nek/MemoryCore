#include "MemoryCore.h"

#include "FlashConfig.h"

using namespace MemoryCore;

MemoryCore::MemoryCore(
    SPIClass& spi,
    uint8_t chipSelectPin)
    : _spi(spi, chipSelectPin),
      _flash(_spi)
{
}

bool MemoryCore::begin()
{
    _spi.begin();

    if (!_flash.begin())
        return false;

    _jedec = _flash.readJEDECID();

    return true;
}

JEDECID MemoryCore::jedecID()
{
    return _jedec;
}

uint64_t MemoryCore::uniqueID()
{
    return _flash.readUniqueID();
}

uint32_t MemoryCore::capacity() const
{
    return _flash.geometry().capacityBytes;
}

uint32_t MemoryCore::pageSize() const
{
    return _flash.geometry().pageSize;
}

uint32_t MemoryCore::sectorSize() const
{
    return _flash.geometry().sectorSize;
}

bool MemoryCore::busy()
{
    return _flash.busy();
}

bool MemoryCore::validRange(
    uint32_t address,
    uint32_t length)
{
#if MEMORYCORE_ENABLE_PARAMETER_CHECK

    if (length == 0)
        return false;

    if ((address + length) > capacity())
        return false;

#endif

    return true;
}

bool MemoryCore::read(
    uint32_t address,
    void* buffer,
    uint32_t length)
{
    if (!validRange(address, length))
        return false;

    _flash.read(address, buffer, length);

    return true;
}

bool MemoryCore::write(
    uint32_t address,
    const void* data,
    uint32_t length)
{
    if (!validRange(address, length))
        return false;

    const uint8_t* src =
        static_cast<const uint8_t*>(data);

    while (length)
    {
        uint32_t pageOffset =
            address % FLASH_PAGE_SIZE;

        uint32_t remainingInPage =
            FLASH_PAGE_SIZE - pageOffset;

        uint32_t chunk =
            min<uint32_t>(remainingInPage, length);

        _flash.pageProgram(
            address,
            src,
            chunk);

        address += chunk;
        src += chunk;
        length -= chunk;
    }

    return true;
}

bool MemoryCore::writeByte(
    uint32_t address,
    uint8_t value)
{
    return write(address, &value, 1);
}

uint8_t MemoryCore::readByte(
    uint32_t address)
{
    uint8_t value = 0xFF;

    read(address, &value, 1);

    return value;
}

bool MemoryCore::eraseSector(
    uint32_t sector)
{
    uint32_t address =
        sector * FLASH_SECTOR_SIZE;

    if (address >= capacity())
        return false;

    _flash.eraseSector(address);

    return true;
}

bool MemoryCore::eraseBlock32K(
    uint32_t block)
{
    uint32_t address =
        block * FLASH_BLOCK32_SIZE;

    if (address >= capacity())
        return false;

    _flash.eraseBlock32K(address);

    return true;
}

bool MemoryCore::eraseBlock64K(
    uint32_t block)
{
    uint32_t address =
        block * FLASH_BLOCK64_SIZE;

    if (address >= capacity())
        return false;

    _flash.eraseBlock64K(address);

    return true;
}

bool MemoryCore::eraseChip()
{
    _flash.eraseChip();
    return true;
}
