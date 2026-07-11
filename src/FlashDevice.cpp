#include "FlashDevice.h"

#include "internal/Commands.h"
#include "FlashStatus.h"
#include "FlashConfig.h"

using namespace MC;

FlashDevice::FlashDevice(SPIBus &spi)
    : _spi(spi)
{
    memset(&_geometry, 0, sizeof(_geometry));
}

bool FlashDevice::begin()
{
    reset();

    JEDECID id = readJEDECID();

    if (!isWinbond(id))
        return false;

    detectGeometry(id);

    return _geometry.capacityBytes != 0;
}

JEDECID FlashDevice::readJEDECID()
{
    JEDECID id{};

    _spi.beginTransaction();

    _spi.transfer(Command::ReadJEDECID);

    id.manufacturer = _spi.transfer(0xFF);
    id.memoryType = _spi.transfer(0xFF);
    id.capacity = _spi.transfer(0xFF);

    _spi.endTransaction();

    return id;
}

uint64_t FlashDevice::readUniqueID()
{
    uint64_t uid = 0;

    _spi.beginTransaction();

    _spi.transfer(Command::ReadUniqueID);

    for (uint8_t i = 0; i < 4; i++)
        _spi.transfer(0x00);

    for (int i = 7; i >= 0; i--)
        ((uint8_t *)&uid)[i] = _spi.transfer(0xFF);

    _spi.endTransaction();

    return uid;
}

uint8_t FlashDevice::readStatus1()
{
    _spi.beginTransaction();

    _spi.transfer(Command::ReadStatus1);

    uint8_t value = _spi.transfer(0xFF);

    _spi.endTransaction();

    return value;
}

uint8_t FlashDevice::readStatus2()
{
    _spi.beginTransaction();

    _spi.transfer(Command::ReadStatus2);

    uint8_t value = _spi.transfer(0xFF);

    _spi.endTransaction();

    return value;
}

uint8_t FlashDevice::readStatus3()
{
    _spi.beginTransaction();

    _spi.transfer(Command::ReadStatus3);

    uint8_t value = _spi.transfer(0xFF);

    _spi.endTransaction();

    return value;
}

bool FlashDevice::busy()
{
    return isBusy(readStatus1());
}

void FlashDevice::waitWhileBusy()
{
    while (busy())
        yield();
}

void FlashDevice::writeEnable()
{
    _spi.beginTransaction();

    _spi.transfer(Command::WriteEnable);

    _spi.endTransaction();
}

void FlashDevice::writeDisable()
{
    _spi.beginTransaction();

    _spi.transfer(Command::WriteDisable);

    _spi.endTransaction();
}

void FlashDevice::read(uint32_t address, void *buffer, uint32_t length)
{
    _spi.beginTransaction();

    _spi.transfer(Command::ReadData);

    sendAddress(address);

    _spi.read((uint8_t *)buffer, length);

    _spi.endTransaction();
}

void FlashDevice::pageProgram(uint32_t address, const void *data, uint16_t length)
{
    writeEnable();

    _spi.beginTransaction();

    _spi.transfer(Command::PageProgram);

    sendAddress(address);

    _spi.write((const uint8_t *)data, length);

    _spi.endTransaction();

    waitWhileBusy();
}

void FlashDevice::eraseSector(uint32_t address)
{
    writeEnable();

    _spi.beginTransaction();

    _spi.transfer(Command::SectorErase);

    sendAddress(address);

    _spi.endTransaction();

    waitWhileBusy();
}

void FlashDevice::eraseBlock32K(uint32_t address)
{
    writeEnable();

    _spi.beginTransaction();

    _spi.transfer(Command::BlockErase32K);

    sendAddress(address);

    _spi.endTransaction();

    waitWhileBusy();
}

void FlashDevice::eraseBlock64K(uint32_t address)
{
    writeEnable();

    _spi.beginTransaction();

    _spi.transfer(Command::BlockErase64K);

    sendAddress(address);

    _spi.endTransaction();

    waitWhileBusy();
}

void FlashDevice::eraseChip()
{
    writeEnable();

    _spi.beginTransaction();

    _spi.transfer(Command::ChipErase);

    _spi.endTransaction();

    waitWhileBusy();
}

void FlashDevice::reset()
{
    _spi.beginTransaction();
    _spi.transfer(Command::EnableReset);
    _spi.endTransaction();

    _spi.beginTransaction();
    _spi.transfer(Command::ResetDevice);
    _spi.endTransaction();

    delay(1);
}

void FlashDevice::powerDown()
{
    _spi.beginTransaction();
    _spi.transfer(Command::PowerDown);
    _spi.endTransaction();
}

void FlashDevice::wakeUp()
{
    _spi.beginTransaction();
    _spi.transfer(Command::ReleasePowerDown);
    _spi.endTransaction();

    delayMicroseconds(30);
}

void FlashDevice::sendAddress(uint32_t address)
{
    _spi.transfer((address >> 16) & 0xFF);
    _spi.transfer((address >> 8) & 0xFF);
    _spi.transfer(address & 0xFF);
}

const FlashGeometry &FlashDevice::geometry() const
{
    return _geometry;
}

void FlashDevice::detectGeometry(const JEDECID &id)
{
    _geometry.capacityBytes = capacityBytes(id.capacity);

    _geometry.pageSize = W25Q_FLASH_PAGE_SIZE;
    _geometry.sectorSize = W25Q_FLASH_SECTOR_SIZE;
    _geometry.block32Size = W25Q_FLASH_BLOCK32_SIZE;
    _geometry.block64Size = W25Q_FLASH_BLOCK64_SIZE;

    if (_geometry.capacityBytes)
    {
        _geometry.pageCount =
            _geometry.capacityBytes / _geometry.pageSize;

        _geometry.sectorCount =
            _geometry.capacityBytes / _geometry.sectorSize;

        _geometry.block32Count =
            _geometry.capacityBytes / _geometry.block32Size;

        _geometry.block64Count =
            _geometry.capacityBytes / _geometry.block64Size;
    }
}
