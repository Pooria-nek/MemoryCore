#include "MemoryCore.h"

MemoryCore::MemoryCore(
    SPIClass &spi,
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

bool MemoryCore::validRange(uint32_t address, uint32_t length)
{
#if MEMORYCORE_ENABLE_PARAMETER_CHECK

    if (length == 0)
        return false;

    if (address >= capacity())
        return false;

    if (length > capacity() - address)
        return false;

#endif

    return true;
}

bool MemoryCore::read(uint32_t address, void *buffer, uint32_t length)
{
    if (!validRange(address, length))
        return false;

    _flash.read(address, buffer, length);

    return true;
}

bool MemoryCore::write(uint32_t address, const void *data, uint32_t length)
{
    if (!validRange(address, length))
        return false;

    const uint8_t *src = static_cast<const uint8_t *>(data);

    while (length)
    {
        uint32_t pageOffset = address % W25Q_FLASH_PAGE_SIZE;

        uint32_t remainingInPage = W25Q_FLASH_PAGE_SIZE - pageOffset;

        uint32_t chunk = min<uint32_t>(remainingInPage, length);

        _flash.pageProgram(address, src, chunk);

        address += chunk;
        src += chunk;
        length -= chunk;
    }

    return true;
}

bool MemoryCore::update(uint32_t address, const void *data, uint32_t length)
{
    if (!validRange(address, length))
        return false;

    const uint8_t *src = static_cast<const uint8_t *>(data);

    while (length)
    {
        uint32_t sector = address / W25Q_FLASH_SECTOR_SIZE;
        uint32_t sectorAddress = sector * W25Q_FLASH_SECTOR_SIZE;

        uint32_t offset = address - sectorAddress;

        uint32_t chunk = W25Q_FLASH_SECTOR_SIZE - offset;

        if (chunk > length)
            chunk = length;

        // Read whole sector
        if (!read(sectorAddress, _sectorBuffer, W25Q_FLASH_SECTOR_SIZE))
            return false;

        uint8_t *oldData = &_sectorBuffer[offset];

        // Already identical
        if (memcmp(oldData, src, chunk) == 0)
        {
            address += chunk;
            src += chunk;
            length -= chunk;
            continue;
        }

        // Can program directly (1 -> 0 only)
        if (!requiresErase(oldData, src, chunk))
        {
            if (!write(address, src, chunk))
                return false;
        }
        else
        {
            // Modify RAM copy
            memcpy(oldData, src, chunk);

            // Erase sector
            if (!eraseSector(sector))
                return false;

            // Rewrite sector
            if (!write(sectorAddress, _sectorBuffer, W25Q_FLASH_SECTOR_SIZE))
                return false;
        }

        address += chunk;
        src += chunk;
        length -= chunk;
    }

    return true;
}

bool MemoryCore::requiresErase(const uint8_t *oldData, const uint8_t *newData, uint32_t length)
{
    while (length--)
    {
        // If any bit must change from 0 -> 1, an erase is required.
        if (((~(*oldData)) & (*newData)) != 0)
            return true;

        oldData++;
        newData++;
    }

    return false;
}

bool MemoryCore::eraseSector(uint32_t sector)
{
    uint32_t address = sector * W25Q_FLASH_SECTOR_SIZE;

    if (address >= capacity())
        return false;

    _flash.eraseSector(address);

    return true;
}

bool MemoryCore::eraseBlock32K(
    uint32_t block)
{
    uint32_t address = block * W25Q_FLASH_BLOCK32_SIZE;

    if (address >= capacity())
        return false;

    _flash.eraseBlock32K(address);

    return true;
}

bool MemoryCore::eraseBlock64K(
    uint32_t block)
{
    uint32_t address = block * W25Q_FLASH_BLOCK64_SIZE;

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
