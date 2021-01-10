#include "ad7606.h"

// uint8_t lowByte;
// uint8_t highByte;

// // Constructor
// AD7606::AD7606(pin_size_t miso, pin_size_t sclk, pin_size_t cs, pin_size_t convst, pin_size_t busy, pin_size_t reset, int frequency) : _cs(cs),
//                                                                                                                                        _convst(convst),
//                                                                                                                                        _busy(busy),
//                                                                                                                                        _reset(reset)
// {
//   //_spi.frequency(frequency);
//   //_spi.format(8, 0);

//   pinMode(_cs, OUTPUT);
//   pinMode(_convst, OUTPUT);
//   pinMode(_reset, OUTPUT);
//   pinMode(_busy, INPUT);
//   resetADC();
// };

// // Resets the AD7606
// void AD7606::resetADC()
// {
//   digitalWrite(_reset, HIGH);
//   digitalWrite(_reset, LOW);
// }

// // Computes and stores the quantization step of the AD7606 as a function of its dynamic range (10 V or 20 V)
// void AD7606::setDR(double DR)
// {
//   _q = (double)DR / 65535.0; // Quantization step
// }

// // Read raw values from all 8 channels
// // rawDataBuffer is a pointer to an array of 8 16-bit integers
// void AD7606::readRAW(int16_t *rawDataBuffer)
// {
//   digitalWrite(_convst, LOW);
//   digitalWrite(_convst, HIGH);

//   // wait for conversions to be completed (low level on BUSY)
//   // while (_busy)
//   // {
//   // }
//   delayMicroseconds(5);

//   Sample adc;

//   // Enable DoutA and DoutB lines and shift-out the conversion results
//   digitalWrite(_cs, LOW);
//   for (char k = 0; k < 4; k++)
//   {
//     // send second command byte and receive first(msb) 4 bits
//     _spi->transfer(0x00);
//     adc.byte.high = _spi->transfer(0x00);

//     // receive last(lsb) 8 bits
//     adc.byte.high = _spi->transfer(0x00);

//     *(rawDataBuffer + k) = adc.value;
//   }
//   digitalWrite(_cs, HIGH);
// }

// // Read analog values from all 8 channels
// // analogDataBuffer is a pointer to an array of 8 doubles
// void AD7606::readAnalog(double *analogDataBuffer)
// {
//   // uint8_t lowByte, highByte;

//   // _convst = 0; // Pulse CONVSTA/CONVSTB to start conversion
//   // wait_us(1);
//   // _convst = 1;
//   // wait_us(5);
//   // //while (_busy) {
//   // // wait for conversions to be completed (low level on BUSY)
//   // //}
//   // _cs = 0; // Enable DOUTA/DOUTB lines and shift-out the conversion results
//   // for (char k = 0; k < 8; k++)
//   // {
//   //   highByte = _spi.write(0x00);
//   //   lowByte = _spi.write(0x00);
//   //   *(analogDataBuffer + k) = (double)((int16_t)((highByte << 8) + lowByte)) * _q;
//   // }
//   // _cs = 1;
// }
