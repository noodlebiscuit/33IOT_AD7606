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
 * AD7606_SAMD21_CPP
 * Support library for the "doukstore" AD7606 Data Acquisition Module 
 * with 8 analogue channels with 16 bit ADC supporting 200KHz sampling 
 *  
***************************************************************************************************/

#include "AD7606_SAMD21.h"

/*
** ================================================================================================
**     CONSTRUCTOR
** ================================================================================================
**     Parameters :
**         cs        - PIN used for SPI chip select (CS)
**         convst    - PIN used to initiate the convertor start (CONVST)
**         busy      - PIN read to determine if the convertor is still busy (BUSY)
**         reset     - PIN used to reset the convertor (RESET)
** ================================================================================================
*/
AD7606_SAMD21::AD7606_SAMD21(pin_size_t cs, pin_size_t convst, pin_size_t busy, pin_size_t reset)
    : _cs(cs),
      _convst(convst),
      _busy(busy),
      _reset(reset)
{
   // bit-bash control of the AD7606 handshake and control pins
   setupControlPins();

   // lastly we reset the ADC
   resetConvertor();
};

/*
** ================================================================================================
**     Method      :  readRaw
**
**     Description :
**         returns a single sample set for N number of channels
** ================================================================================================
*/
void AD7606_SAMD21::readRAW(int16_t *rawDataBuffer, int channels)
{
   // toggle the convertor start line
   setConvertorStart(LOW);
   setConvertorStart(HIGH);

   // wait for conversions to be completed (low level on BUSY)
   while (read_convertorBusy())
   {
   }

   // Enable DoutA and DoutB lines and shift-out the conversion results
   setChipSelect(LOW);

   // read the channels
   for (char k = 0; k < channels; k++)
   {
      adc.byte.high = SPI.transfer(0x00);
      adc.byte.low = SPI.transfer(0x00);
      *(rawDataBuffer + k) = adc.value;
   }

   // toggle the chip select line again
   setChipSelect(HIGH);
}

/*
** ================================================================================================
**     Method      :  SetupControlPins
**
**     Description :
**         bit-bash control of the AD7606 handshake and control pins 
** ================================================================================================
*/
void AD7606_SAMD21::setupControlPins()
{
   pinConvst = digitalPinToBitMask(_convst);
   modeConvst = portModeRegister(digitalPinToPort(_convst));
   outConvst = portOutputRegister(digitalPinToPort(_convst));

   pinChipSelect = digitalPinToBitMask(_cs);
   modeChipSelect = portModeRegister(digitalPinToPort(_cs));
   outChipSelect = portOutputRegister(digitalPinToPort(_cs));

   pinReset = digitalPinToBitMask(_reset);
   modeReset = portModeRegister(digitalPinToPort(_reset));
   outReset = portOutputRegister(digitalPinToPort(_reset));

   pinBusy = digitalPinToBitMask(_busy);
   modeBusy = portModeRegister(digitalPinToPort(_busy));
   inBusy = portInputRegister(digitalPinToPort(_busy));

   // set the RESET, CONVST and CS pins as output
   *modeConvst |= pinConvst;
   *modeChipSelect |= pinChipSelect;
   *modeReset |= pinReset;
   *modeBusy |= pinBusy;
}

/*
** ================================================================================================
**     Method      :  resetConvertor
**
**     Description :
**         toggles the AD7606 RESET line HIGH then LOW
** ================================================================================================
*/
void AD7606_SAMD21::resetConvertor()
{
   setReset(HIGH);
   delayMicroseconds(10);
   setReset(LOW);
}

/*
** ================================================================================================
**     Method      :  setConvertorStart
**
**     Description :
**         set the convertor start (CONVST) line high or low
** ================================================================================================
*/
void AD7606_SAMD21::setConvertorStart(PinStatus status)
{
   *outConvst |= pinConvst;
   *outConvst = pinConvst & status;
}

/*
** ================================================================================================
**     Method      :  setChipSelect
**
**     Description :
**         set the SPI chip select (CS) line high or low
** ================================================================================================
*/
void AD7606_SAMD21::setChipSelect(PinStatus status)
{
   *outChipSelect |= pinChipSelect;
   *outChipSelect = pinChipSelect & status;
}

/*
** ================================================================================================
**     Method      :  setReset
**
**     Description :
**         set the AD7606 RESET line high or low
** ================================================================================================
*/
void AD7606_SAMD21::setReset(PinStatus status)
{
   *outReset |= pinReset;
   *outReset = pinReset & status;
}

/*
** ================================================================================================
**     Method      :  read_convertorBusy
**
**     Description :
**         monitors the ADC BUSY\ line
**
**     Returns  :
**         returns true while port is busy
** ================================================================================================
*/
bool AD7606_SAMD21::read_convertorBusy()
{
   return (REG_PORT_IN0 & (PORT_PA18)) == PORT_PA18;
}
