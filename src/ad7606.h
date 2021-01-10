
#ifndef AD7606_H
#include <Wire.h>

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <SPI.h>

// //-----------------------------------------------------------------------------

// /**
//    * Defines 16 bit SPI data. The structure implements an easy
//    * access to each byte.
//    */
// union SpiData
// {
//     uint16_t value; /**< value */
//     struct
//     {
//         uint8_t loByte; /**< low byte */
//         uint8_t hiByte; /**< high byte */
//     };
// };

// //
// // 16 bit ADC dataword split into two byte elements
// //
// union Sample
// {
//     int16_t value;
//     struct Byte
//     {
//         uint8_t low, high;
//     } byte;
// };

// class AD7606
// {
// private:
//     SPIClass *_spi;
//     pin_size_t _cs;
//     pin_size_t _convst;
//     pin_size_t _busy;
//     pin_size_t _reset;
//     double _q;
//     SpiData adc;

// public:
//     AD7606(pin_size_t miso, pin_size_t sclk, pin_size_t cs, pin_size_t convst, pin_size_t busy, pin_size_t reset, int frequency); // Constructor
//     void resetADC();
//     void setDR(double);        // Set dynamic range (10 V or 20 V), as a function of RANGE pin (0 => DR = +/- 5 V, 1 => DR = +/- 10 V)
//     void readRAW(int16_t *);   // Read raw values from ADC
//     void readAnalog(double *); // Read analog values
// };

#endif
