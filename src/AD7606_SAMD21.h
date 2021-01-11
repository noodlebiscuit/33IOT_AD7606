
/**************************************************************************************************
 * @author Alex Pinkerton
 *
 * @section (c) 2021, MIT LICENSE@
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: The above copyright notice and this 
 * permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * AD7606_SAMD21_H
 * Support library for the "doukstore" AD7606 Data Acquisition Module 
 * with 8 analogue channels with 16 bit ADC supporting 200KHz sampling 
 *  
***************************************************************************************************/

#ifndef AD7606_SAMD21_H
#include <Wire.h>

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <SPI.h>

#define REGTYPE uint32_t

/**************************************************************************************************
 * 16 bit SPI data type
*/
union Sample
{
   int16_t value;
   struct Byte
   {
      uint8_t low, high;
   } byte;
};

/**
 * CLASS HEADER
*/
class AD7606_SAMD21
{
private:
   // allow direct access to the AD7606 CONVST pin
   REGTYPE pinConvst;
   volatile REGTYPE *modeConvst;
   volatile REGTYPE *outConvst;

   // allow direct access to the SPI CHIP SELECT pin
   REGTYPE pinChipSelect;
   volatile REGTYPE *modeChipSelect;
   volatile REGTYPE *outChipSelect;

   // allow direct access to the AD7606 RESET pin
   REGTYPE pinReset;
   volatile REGTYPE *modeReset;
   volatile REGTYPE *outReset;
   
   // allow direct access to the AD7606 BUSY pin
   REGTYPE pinBusy;
   volatile REGTYPE *modeBusy;
   volatile REGTYPE *inBusy;

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
   void resetConvertor();
   void readRAW(int16_t *, int);
};

#endif
