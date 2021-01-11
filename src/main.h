#include <Arduino.h>
#include <Wire.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "Stream.h"
#include "ad7606.h"

#pragma once
#include <stdint.h>

//-----------------------------------------------------------------------------

#define SERIAL_BAUD_RATE 115200 // serial port baud rate

#define SCLK 13  // SPI clock
#define MISO 12  // SPI master IN slave OUT pin
#define MOSI 11  // SPI master OUT slave IN pin
#define CS 10    // SPI chip select             -PA21
#define CONVST 9 // AD7606 start conversion     -PA20
#define BUSY 8   // AD7606 is busy              -PA18
#define RESET 7  // AD7606 reset                -PA06

#define FREQUENCY 3200000 // ADS clock speed (10MHz)
#define SPI_DATA_BITS 8       // number of data bits

union Sample
{
    int16_t value;
    struct Byte
    {
        uint8_t low, high;
    } byte;
};


void readRAW(int16_t *, int);
bool read_convertorBusy();
void setConvertorStart(PinStatus);
void setChipSelect(PinStatus);
