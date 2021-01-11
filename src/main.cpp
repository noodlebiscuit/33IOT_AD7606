#include "main.h"




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
   adc.resetConvertor();
}


void loop()
{
   int16_t *message = new int16_t[8];

   uint32_t t1;
   uint32_t t2;

   t1 = micros();

   for (int j = 0; j < 1000; ++j)
   {
   adc.readRAW(message, 4);
   // for (int i = 0; i < 4; ++i)
   // {
   //    Serial.print(message[i]);
   //    Serial.print(" ");
   // }

   //Serial.println("------------");
   }

   t2 = micros();

   delete[] message;

   // sampling time
   Serial.print("Samples: ");
   Serial.println(1000);
   Serial.print("Sampling time: ");
   Serial.print(static_cast<double>(t2 - t1) / 1000, 4);
   Serial.println("ms");
   delay(1000);
}

