#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "Stream.h"
#include "AD7606_SAMD21.h"

#pragma once
#include <stdint.h>

//-----------------------------------------------------------------------------

#define SERIAL_BAUD_RATE 115200 // serial port baud rate

#define CS 10              // SPI chip select             -PA21
#define CONVST 9           // AD7606 start conversion     -PA20
#define BUSY 8             // AD7606 is busy              -PA18
#define RESET 7            // AD7606 reset                -PA06
#define FREQUENCY 10000000 // ADS clock speed (10MHz)

// construct the AD7606 library
AD7606_SAMD21 adc(CS, CONVST, BUSY, RESET);
