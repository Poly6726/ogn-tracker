#pragma once

// GPS
#define GPS_UART UART_NUM_0  // UART for GPS
#define GPS_PinTx      21 // Tx-Data
#define GPS_PinRx      20 // Rx-Data
//#define GPS_PinPPS     0 // PPS
#define GPS_PinEna     3 // enable/wakeup

// SX1262 or SX1276 RF chip
#define Radio_PinRST    1 //
#define Radio_PinSCK    4 // SCK
#define Radio_PinMOSI   6 // MOSI
#define Radio_PinMISO   5 // MISO
#define Radio_PinCS     7 // CS
#define Radio_PinIRQ1   3 // IRQ
#define Radio_PinIRQ    Radio_PinIRQ1 // IRQ, DIO0 for SX1276
#define Radio_PinBusy   2 // Busy: only for SX1262


// External I2C for BME280, RTC, OLED, Magnetic sensor
#define I2C_PinSCL    9 // SCL
#define I2C_PinSDA    8 // SDA

// Internal I2C for PMU
//#define PMU_I2C_PinSCL    1 // SCL
//#define PMU_I2C_PinSDA    2 // SDA

// SD card and IMU       CONN   GPIO
// SD_CS                  B-9    47
// IMU_INT                B-7    33
// IMU_CS                 B-5    34
// SD_MOSI   SPI_MOSI     B-3    35
// SD_SCK    SPI_CSK      B-1    36
// SD_MISO   SPI_MISO      75    37
#define IMU_PinCS  34
#define SD_PinCS   47
#define SD_PinMOSI 35
#define SD_PinSCK  36
#define SD_PinMISO 37