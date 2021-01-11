#include "main.h"

//AD7606 ad7606();

Sample adc;

#define REGTYPE uint32_t
REGTYPE pinConvst;
volatile REGTYPE *modeConvst;
volatile REGTYPE *outConvst;

REGTYPE pinChipSelect;
volatile REGTYPE *modeChipSelect;
volatile REGTYPE *outChipSelect;

void setup()
{
  // set the hardware serial baud rate
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Initialise AD7606 board");

  // initialize SPI interface for MCP3208
  SPISettings settings(FREQUENCY, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);

  pinMode(CS, OUTPUT);
  pinMode(CONVST, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(BUSY, INPUT);

  digitalWrite(RESET, HIGH);
  digitalWrite(RESET, LOW);

  pinConvst = digitalPinToBitMask(CONVST);
  modeConvst = portModeRegister(digitalPinToPort(CONVST));
  outConvst = portOutputRegister(digitalPinToPort(CONVST));

  pinChipSelect = digitalPinToBitMask(CS);
  modeChipSelect = portModeRegister(digitalPinToPort(CS));
  outChipSelect = portOutputRegister(digitalPinToPort(CS));

  // set pin 13 port as ouput
  *modeConvst |= pinConvst;
}

void loop()
{
  int16_t *message = new int16_t[8];

  //uint32_t t1;
  //uint32_t t2;

  //t1 = micros();

  //for (int j = 0; j < 1000; ++j)
  //{
  readRAW(message, 8);
  for (int i = 0; i < 8; ++i)
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

void readRAW(int16_t *rawDataBuffer, int channels)
{
  // toggle the convertor start line
  //digitalWrite(CONVST, LOW);
  //digitalWrite(CONVST, HIGH);

  setConvertorStart(LOW);
  setConvertorStart(HIGH);

  // wait for conversions to be completed (low level on BUSY)
  while (read_convertorBusy())
  {
  }

  // Enable DoutA and DoutB lines and shift-out the conversion results
  //digitalWrite(CS, LOW);

  setChipSelect(LOW);
  for (char k = 0; k < channels; k++)
  {
    adc.byte.high = SPI.transfer(0x00);
    adc.byte.low = SPI.transfer(0x00);
    *(rawDataBuffer + k) = adc.value;
  }
  setChipSelect(HIGH);
}

/*
** ================================================================================================
**     Method      :  setConvertorStart
**
**     Description :
**         monitors the ADC BUSY\ line
**
**     Returns  :
**         returns true while line CB2 is busy
** ================================================================================================
*/
void setConvertorStart(PinStatus status)
{
  *outConvst |= pinConvst;
  *outConvst = pinConvst & status;
}

/*
** ================================================================================================
**     Method      :  setChipSelect
**
**     Description :
**         monitors the ADC BUSY\ line
**
**     Returns  :
**         returns true while line CB2 is busy
** ================================================================================================
*/
void setChipSelect(PinStatus status)
{
  *outChipSelect |= pinChipSelect;
  *outChipSelect = pinChipSelect & status;
}

/*
** ================================================================================================
**     Method      :  read_convertorBusy
**
**     Description :
**         monitors the ADC BUSY\ line
**
**     Returns  :
**         returns true while line CB2 is busy
** ================================================================================================
*/
bool read_convertorBusy()
{
  return (REG_PORT_IN0 & (PORT_PA18)) == PORT_PA18;
}
