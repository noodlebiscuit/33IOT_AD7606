#include "AD7606_SAMD21.h"

/*
** ================================================================================================
**     CONSTRUCTOR
** ================================================================================================
**     Parameters :
**         cs        - PIN used for SPI chip select
**         convst    - PIN used to initiate the convertor start
**         busy      - PIN read to determine if the convertor is still busy
**         reset     - PIN used to reset the convertor
**         frequency - sets the SPI clock frequency
** ================================================================================================
*/
AD7606_SAMD21::AD7606_SAMD21(pin_size_t cs, pin_size_t convst, pin_size_t busy, pin_size_t reset, int frequency)
    : _cs(cs),
      _convst(convst),
      _busy(busy),
      _reset(reset),
      _frequency(frequency)
{
   // use basic ARDUINO API
   pinMode(_reset, OUTPUT);
   pinMode(_busy, INPUT);

   // initialize SPI interface
   SPISettings settings(frequency, MSBFIRST, SPI_MODE0);
   SPI.begin();
   SPI.beginTransaction(settings);

   // bit-bash control of the AD7606 handshake and control pins
   setupControlPins();

   // lastly we reset the ADC
   resetADC();
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

   // set the RESET, CONVST and CS pins as output
   *modeConvst |= pinConvst;
   *modeChipSelect |= pinChipSelect;
   *modeReset |= pinReset;
}

/*
** ================================================================================================
**     Method      :  reset
**
**     Description :
**         toggles the AD7606 RESET line HIGH then LOW
** ================================================================================================
*/
void AD7606_SAMD21::resetADC()
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
