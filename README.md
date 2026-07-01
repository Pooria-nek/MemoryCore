# MemoryCore

A lightweight, reusable, and easy-to-use SPI Flash memory library for Winbond W25Qxx series chips.

MemoryCore is designed for Arduino-compatible platforms with a focus on STM32, providing a clean object-oriented API for reading, writing, and erasing external SPI Flash memories.

---

## Features

- ✅ W25Q16 support (initial release)
- ✅ Designed to support the complete W25Qxx family
  - W25Q16
  - W25Q32
  - W25Q64
  - W25Q128
- ✅ Automatic page boundary handling
- ✅ Fast sequential read
- ✅ Sector, 32 KB block, 64 KB block and chip erase
- ✅ JEDEC ID detection
- ✅ Unique ID reading
- ✅ Configurable SPI interface
- ✅ Lightweight and portable
- ✅ PlatformIO compatible
- ✅ Arduino framework compatible
- ✅ GPL-3.0 licensed

---

## Supported Platforms

- STM32 (recommended)
- ESP32
- ESP8266
- AVR (Arduino Uno, Mega, Nano)
- Raspberry Pi Pico (Arduino Core)
- Any Arduino-compatible platform with SPI support

---

## Installation

### PlatformIO

Add the library to your `platformio.ini`:

```ini
lib_deps =
    Pooria-nek/MemoryCore
```

Or install it from the PlatformIO Library Registry.

### Manual Installation

Clone the repository into your project's `lib` folder:

```text
lib/
└── MemoryCore/
```

---

## Wiring

Example for STM32F103:

| Flash | STM32 |
|--------|--------|
| CS     | PA4    |
| CLK    | PA5    |
| MISO   | PA6    |
| MOSI   | PA7    |
| VCC    | 3.3V   |
| GND    | GND    |

---

## Quick Start

```cpp
#include <SPI.h>
#include <MemoryCore.h>

MemoryCore flash(SPI, PA4);

void setup()
{
    Serial.begin(115200);

    if (!flash.begin())
    {
        Serial.println("Flash not detected!");
        while (true);
    }

    flash.eraseSector(0);

    const char message[] = "Hello MemoryCore";

    flash.write(0, message, sizeof(message));

    char buffer[32];

    flash.read(0, buffer, sizeof(message));

    Serial.println(buffer);
}

void loop()
{
}
```

---

## Basic API

### Initialization

```cpp
bool begin();
```

Initialize the flash memory and detect its geometry.

---

### Read

```cpp
bool read(
    uint32_t address,
    void* buffer,
    uint32_t length);
```

---

### Write

```cpp
bool write(
    uint32_t address,
    const void* data,
    uint32_t length);
```

Automatically handles page boundaries.

---

### Erase

```cpp
eraseSector(uint32_t sector);

eraseBlock32K(uint32_t block);

eraseBlock64K(uint32_t block);

eraseChip();
```

---

### Information

```cpp
capacity();

pageSize();

sectorSize();

jedecID();

uniqueID();
```

---

## Memory Layout

For W25Q16:

| Property | Value |
|----------|--------|
| Capacity | 2 MB |
| Page Size | 256 Bytes |
| Sector Size | 4 KB |
| 32 KB Blocks | Yes |
| 64 KB Blocks | Yes |

---

## Examples

The `examples` directory contains:

- BasicReadWrite
- SpeedTest
- DumpFlash
- WearLeveling (planned)

---

## Roadmap

### Version 0.1

- Raw flash driver
- Read / Write
- Page programming
- Sector erase
- Block erase
- Chip erase
- JEDEC detection

### Version 0.2

- CRC verification
- Typed object read/write
- Verification after write

### Version 0.3

- EEPROM emulation
- Wear leveling

### Version 0.4

- Circular logger
- Configuration storage

### Version 1.0

- Stable API
- Full W25Qxx family support
- Extensive documentation

---

## Project Structure

```
MemoryCore/
│
├── examples/
├── docs/
├── src/
│   ├── MemoryCore.h
│   ├── MemoryCore.cpp
│   ├── W25Q.cpp
│   ├── W25Q.h
│   ├── FlashDevice.cpp
│   ├── FlashDevice.h
│   ├── SPIBus.cpp
│   ├── SPIBus.h
│   └── internal/
│       ├── Commands.h
│       ├── JEDEC.h
│       └── CRC16.h
│
├── LICENSE
├── README.md
└── library.json
```

---

## License

MemoryCore is released under the GPL-3.0 License.

See the LICENSE file for details.

---

## Author

Created and maintained by **Pooria**.

Contributions, bug reports, and feature requests are welcome.
