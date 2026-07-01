#ifndef MEMORYCORE_FLASHCONFIG_H
#define MEMORYCORE_FLASHCONFIG_H

#include <Arduino.h>

/*
 * ============================================================================
 * MemoryCore Configuration
 * ============================================================================
 *
 * Modify these values if needed before compiling the library.
 *
 * Most users should keep the default values.
 *
 */

// Enable parameter validation
#ifndef MEMORYCORE_ENABLE_PARAMETER_CHECK
#define MEMORYCORE_ENABLE_PARAMETER_CHECK 1
#endif

// Verify data after every write (future feature)
#ifndef MEMORYCORE_ENABLE_WRITE_VERIFY
#define MEMORYCORE_ENABLE_WRITE_VERIFY 0
#endif

// SPI clock frequency
#ifndef MEMORYCORE_SPI_CLOCK
#define MEMORYCORE_SPI_CLOCK 8000000UL
#endif

// SPI mode used by Winbond W25Qxx
#ifndef MEMORYCORE_SPI_MODE
#define MEMORYCORE_SPI_MODE SPI_MODE0
#endif

// Bit order
#ifndef MEMORYCORE_SPI_BIT_ORDER
#define MEMORYCORE_SPI_BIT_ORDER MSBFIRST
#endif

// Page size (bytes)
constexpr uint16_t FLASH_PAGE_SIZE = 256;

// Sector size (bytes)
constexpr uint32_t FLASH_SECTOR_SIZE = 4096;

// 32 KB block size
constexpr uint32_t FLASH_BLOCK32_SIZE = 32768;

// 64 KB block size
constexpr uint32_t FLASH_BLOCK64_SIZE = 65536;

#endif // MEMORYCORE_FLASHCONFIG_H
