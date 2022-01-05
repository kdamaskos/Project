/*
* PCF8574(A) Remote 8-bit I/O expander for I2C-bus
* Copyright (c) 2012 Bas van Drunen Littel
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef __PCF8574_H
#define __PCF8574_H

#define VERSION 1.0

#include <mbed.h>

#define PCF8574_I2C_ADDRESS     0x40
#define PCF8574A_I2C_ADDRESS    0x70
#define PCF8574_TYPE            false
#define PCF8574A_TYPE           true

class PCF8574 {
public:
    PCF8574(I2C* _interface, unsigned char _chipselect, bool _type);
    ~PCF8574(void);
    
    unsigned char ReadByte(void);
    void WriteByte(unsigned char byte);
private:
    I2C* i2c; // Communication interface
    unsigned char address; //I2C address
};
#endif