#include "main.h"


// construct the AD7606 library
AD7606_SAMD21 adc(CS,CONVST,BUSY, RESET);


void setup()
{
   // set the hardware serial baud rate
   Serial.begin(SERIAL_BAUD_RATE);
   Serial.println("Initialise AD7606 board");

   // initialize SPI interface
   SPISettings settings(FREQUENCY, MSBFIRST, SPI_MODE0);
   SPI.begin();
   SPI.beginTransaction(settings);

   // reset the ADC
   adc.resetADC();
}


void loop()
{
   int16_t *message = new int16_t[8];

   //uint32_t t1;
   //uint32_t t2;

   //t1 = micros();

   //for (int j = 0; j < 1000; ++j)
   //{
   adc.readRAW(message, 4);
   for (int i = 0; i < 4; ++i)
   {
      Serial.print(message[i]);
      Serial.print(" ");
   }

   Serial.println("------------");
   //}

   //t2 = micros();

   delete[] message;

   // // sampling time
   // Serial.print("Samples: ");
   // Serial.println(1000);
   // Serial.print("Sampling time: ");
   // Serial.print(static_cast<double>(t2 - t1) / 1000, 4);
   // Serial.println("ms");
   delay(1000);
}


// /*
// ** ================================================================================================
// **     Method      :  readRaw
// **
// **     Description :
// **         returns a single sample set for N number of channels
// ** ================================================================================================
// */
// void readRAW(int16_t *rawDataBuffer, int channels)
// {
//    // toggle the convertor start line
//    setConvertorStart(LOW);
//    setConvertorStart(HIGH);

//    // wait for conversions to be completed (low level on BUSY)
//    while (read_convertorBusy())
//    {
//    }

//    // Enable DoutA and DoutB lines and shift-out the conversion results
//    setChipSelect(LOW);

//    // read the channels
//    for (char k = 0; k < channels; k++)
//    {
//       adc.byte.high = SPI.transfer(0x00);
//       adc.byte.low = SPI.transfer(0x00);
//       *(rawDataBuffer + k) = adc.value;
//    }

//    // toggle the chip select line again
//    setChipSelect(HIGH);
// }

// /*
// ** ================================================================================================
// **     Method      :  SetupControlPins
// **
// **     Description :
// **         Uses low level 
// ** ================================================================================================
// */
// void setupControlPins()
// {
//    pinConvst = digitalPinToBitMask(CONVST);
//    modeConvst = portModeRegister(digitalPinToPort(CONVST));
//    outConvst = portOutputRegister(digitalPinToPort(CONVST));

//    pinChipSelect = digitalPinToBitMask(CS);
//    modeChipSelect = portModeRegister(digitalPinToPort(CS));
//    outChipSelect = portOutputRegister(digitalPinToPort(CS));

//    pinReset = digitalPinToBitMask(RESET);
//    modeReset = portModeRegister(digitalPinToPort(RESET));
//    outReset = portOutputRegister(digitalPinToPort(RESET));

//    // set the RESET, CONVST and CS pins as output
//    *modeConvst |= pinConvst;
//    *modeChipSelect |= pinChipSelect;
//    *modeReset |= pinReset;
// }

// /*
// ** ================================================================================================
// **     Method      :  reset
// **
// **     Description :
// **         toggles the AD7606 RESET line HIGH then LOW
// ** ================================================================================================
// */
// void reset()
// {
//    setReset(HIGH);
//    delayMicroseconds(1);
//    setReset(LOW);
// }

// /*
// ** ================================================================================================
// **     Method      :  setConvertorStart
// **
// **     Description :
// **         set the convertor start (CONVST) line high or low
// ** ================================================================================================
// */
// void setConvertorStart(PinStatus status)
// {
//    *outConvst |= pinConvst;
//    *outConvst = pinConvst & status;
// }

// /*
// ** ================================================================================================
// **     Method      :  setChipSelect
// **
// **     Description :
// **         set the SPI chip select (CS) line high or low
// ** ================================================================================================
// */
// void setChipSelect(PinStatus status)
// {
//    *outChipSelect |= pinChipSelect;
//    *outChipSelect = pinChipSelect & status;
// }

// /*
// ** ================================================================================================
// **     Method      :  setReset
// **
// **     Description :
// **         set the AD7606 RESET line high or low
// ** ================================================================================================
// */
// void setReset(PinStatus status)
// {
//    *outReset |= pinReset;
//    *outReset = pinReset & status;
// }

// /*
// ** ================================================================================================
// **     Method      :  read_convertorBusy
// **
// **     Description :
// **         monitors the ADC BUSY\ line
// **
// **     Returns  :
// **         returns true while port is busy
// ** ================================================================================================
// */
// bool read_convertorBusy()
// {
//    return (REG_PORT_IN0 & (PORT_PA18)) == PORT_PA18;
// }
