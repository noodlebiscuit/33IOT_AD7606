#include "main.h"

//AD7606 ad7606();

//SPIClass *_spi;

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
}

void loop()
{
  int16_t *message = new int16_t[4];

  readRAW(message);

  for (int i = 0; i < 8; ++i)
  {
    Serial.print(message[i]);
    Serial.print(" ");
  }

  Serial.println("------------");

  delay(100);

  delete[] message;
}

void readRAW(int16_t *rawDataBuffer)
{
  digitalWrite(CONVST, LOW);
  digitalWrite(CONVST, HIGH);

  // wait for conversions to be completed (low level on BUSY)
  // while (_busy)
  // {
  // }
  delayMicroseconds(5);

  Sample adc;

  // Enable DoutA and DoutB lines and shift-out the conversion results
  digitalWrite(CS, LOW);
  for (char k = 0; k < 8; k++)
  {
    // send second command byte and receive first(msb) 4 bits
    adc.byte.high = SPI.transfer(0x00);

    // receive last(lsb) 8 bits
    adc.byte.low = SPI.transfer(0x00);

    *(rawDataBuffer + k) = adc.value;
  }
  digitalWrite(CS, HIGH);
}
