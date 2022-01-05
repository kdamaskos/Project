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

#include "pcf8574.h"

PCF8574::PCF8574(I2C* _interface, unsigned char _chipselect, bool _type)
    : i2c(_interface)
{
    if (_type == PCF8574_TYPE) {
        address = (_chipselect << 1) | PCF8574_I2C_ADDRESS;
    } else {
        address = (_chipselect << 1) | PCF8574A_I2C_ADDRESS;
    }
}

PCF8574::~PCF8574() {}

unsigned char PCF8574::ReadByte()
{
    char data[1];
    i2c->read(address,data,1);
    return data[0];
}

void PCF8574::WriteByte(unsigned char byte)
{
    unsigned char data[1];
    
    data[0]=byte;
    i2c->write(address,(char *)data,1);
}