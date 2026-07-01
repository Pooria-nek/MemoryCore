class MemoryCore
{
public:

    bool begin();

    bool eraseChip();

    bool eraseSector(uint32_t sector);

    bool eraseBlock32K(uint32_t block);

    bool eraseBlock64K(uint32_t block);

    bool write(
        uint32_t address,
        const void* data,
        uint32_t length);

    bool read(
        uint32_t address,
        void* data,
        uint32_t length);

    bool writeByte(
        uint32_t address,
        uint8_t value);

    uint8_t readByte(
        uint32_t address);

    bool writeStruct(
        uint32_t address,
        const void* object,
        uint32_t size);

    bool readStruct(
        uint32_t address,
        void* object,
        uint32_t size);

    uint32_t capacity();

    uint16_t pageSize();

    uint32_t sectorSize();

    uint32_t blockSize();

    bool busy();

    void waitBusy();

    uint32_t uniqueID();

    uint32_t jedecID();

};
