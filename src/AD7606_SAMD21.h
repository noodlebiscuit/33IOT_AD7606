
#ifndef AD7606_SAMD21_H
#include <Wire.h>

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <SPI.h>
#include <Arduino.h>

#define REGTYPE uint32_t

//-----------------------------------------------------------------------------

//
// 16 bit ADC dataword split into two byte elements
//
union Sample
{
   int16_t value;
   struct Byte
   {
      uint8_t low, high;
   } byte;
};

class AD7606_SAMD21
{
private:
   REGTYPE pinConvst;
   volatile REGTYPE *modeConvst;
   volatile REGTYPE *outConvst;

   REGTYPE pinChipSelect;
   volatile REGTYPE *modeChipSelect;
   volatile REGTYPE *outChipSelect;

   REGTYPE pinReset;
   volatile REGTYPE *modeReset;
   volatile REGTYPE *outReset;

   pin_size_t _cs;
   pin_size_t _convst;
   pin_size_t _busy;
   pin_size_t _reset;
   Sample adc;

   bool read_convertorBusy();
   void setConvertorStart(PinStatus);
   void setChipSelect(PinStatus);
   void setReset(PinStatus);
   void setupControlPins();

public:
   AD7606_SAMD21(pin_size_t cs, pin_size_t convst, pin_size_t busy, pin_size_t reset); 
   void resetADC();
   void readRAW(int16_t*, int);
};

#endif
