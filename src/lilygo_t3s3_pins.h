#pragma once

// GPS
#define GPS_UART UART_NUM_1  // UART for GPS
#define GPS_PinTx      43 // Tx-Data
#define GPS_PinRx      44 // Rx-Data
#define GPS_PinPPS     39 // PPS
#define GPS_PinEna     40 // enable/wakeup

// SX1262 RF chip
#define Radio_PinRST   8 //
#define Radio_PinSCK   5 // SCK
#define Radio_PinMOSI  6 // MOSI
#define Radio_PinMISO  3 // MISO
#define Radio_PinCS    7 // CS
#define Radio_PinIRQ1  33 // IRQ. Is it DIO0(?) or maybe DIO1(33)?
#define Radio_PinBusy  34 // Busy: only for SX1262

// #define I2C_PinSCL    41 // SCL
// #define I2C_PinSDA    42 // SDA

// External I2C for BME280, RTC, OLED, Magnetic sensor
#define I2C_PinSCL    17 // SCL
#define I2C_PinSDA    18 // SDA

// Internal I2C for PMU
#define PMU_I2C_PinSCL    41 // SCL
#define PMU_I2C_PinSDA    42 // SDA

// SD card and IMU       CONN   GPIO
// SD_CS                  B-9    47
// IMU_INT                B-7    33
// IMU_CS                 B-5    34
// SD_MOSI   SPI_MOSI     B-3    35
// SD_SCK    SPI_CSK      B-1    36
// SD_MISO   SPI_MISO      75    37
#define IMU_PinCS  47
#define SD_PinCS   13
#define SD_PinMOSI 11
#define SD_PinSCK  14
#define SD_PinMISO 2

