 /* mbed UniGraphic library - PAR16 protocol class
 * Copyright (c) 2015 Giuliano Dianda
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * Derived work of:
 *
 * mbed library for 240*320 pixel display TFT based on ILI9341 LCD Controller
 * Copyright (c) 2013 Peter Drescher - DC2PD
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "platform.h" 
#if DEVICE_PORTINOUT 
 
#include "PAR16.h"

PAR16::PAR16(PortName port, PinName CS, PinName reset, PinName DC, PinName WR, PinName RD)
    : _port(port,0xFFFF), _CS(CS), _reset(reset), _DC(DC), _WR(WR), _RD(RD)
{
    _reset = 1;
    _DC=1;
    _WR=1;
    _RD=1;
    _CS=1;
    _port.mode(PullNone);
    _port.output(); // will re-enable our GPIO port
    hw_reset();    
}

void PAR16::wr_cmd8(unsigned char cmd)
{      
    _DC = 0; // 0=cmd
    _port.write(cmd);      // write 8bit
    _WR=0;
    _WR=1;
    _DC = 1; // 1=data next
}
void PAR16::wr_data8(unsigned char data)
{
    _port.write(data);    // write 8bit
    _WR=0;
    _WR=1;
}
void PAR16::wr_cmd16(unsigned short cmd)
{    
    _DC = 0; // 0=cmd
    _port.write(cmd>>8);      // write 8bit
    _WR=0;
    _WR=1;
    _port.write(cmd&0xFF);      // write 8bit
    _WR=0;
    _WR=1;
    _DC = 1; // 1=data next
}
void PAR16::wr_data16(unsigned short data)
{
    _port.write(data>>8);    // write 8bit
    _WR=0;
    _WR=1;
    _port.write(data&0xFF);    // write 8bit
    _WR=0;
    _WR=1;
}
void PAR16::wr_gram(unsigned short data)
{
    _port.write(data);    // write 16bit
    _WR=0;
    _WR=1;
}
void PAR16::wr_gram(unsigned short data, unsigned int count)
{
    while(count)
    {
        _port.write(data);    // rewrite even if same data, otherwise too much fast
        _WR=0;
        _WR=1;
        count--;
    }
}
void PAR16::wr_grambuf(unsigned short* data, unsigned int lenght)
{
    while(lenght)
    {
        _port.write(*data);    // write 16bit
        _WR=0;
        _WR=1;
        data++;
        lenght--;
    }
}
unsigned short PAR16::rd_gram(bool convert)
{
    unsigned int r=0;
   _port.input();
   
    _RD = 0;
    _port.read(); //dummy read
    _RD = 1;
    
    _RD = 0;
  //  _RD = 0; // add wait
    r |= _port.read();
    _RD = 1;
    if(convert)
    {
        r <<= 8;
        _RD = 0;
  //      _RD = 0; // add wait
        r |= _port.read()>>8; //MSB of port read is blue, LSB is red of next pixel
        _RD = 1;
        // gram is 18bit/pixel, if you set 16bit/pixel (cmd 3A), during writing the 16bits are expanded to 18bit
        // during reading, you read the raw 18bit gram
        r = RGB24to16((r&0xFF0000)>>16, (r&0xFF00)>>8, r&0xFF);// 18bit pixel padded to 24bits, rrrrrr00_gggggg00_bbbbbb00, converted to 16bit
    }
    _port.output();
    return (unsigned short)r;
}
unsigned int PAR16::rd_reg_data32(unsigned char reg)
{
    wr_cmd8(reg);
    unsigned int r=0;
  //  _DC = 1; // 1=data
   _port.input();
   
    _RD = 0;
    _port.read(); //dummy read
    _RD = 1;
    
    _RD = 0;
//    _RD = 0; // add wait
    r |= (_port.read()&0xFF);
    r <<= 8;
    _RD = 1;
    
    _RD = 0;
//    _RD = 0; // add wait
    r |= (_port.read()&0xFF);
    r <<= 8;
    _RD = 1;
    
    _RD = 0;
//    _RD = 0; // add wait
    r |= (_port.read()&0xFF);
    r <<= 8;
    _RD = 1;
    
    _RD = 0;
//    _RD = 0; // add wait
    r |= (_port.read()&0xFF);
    _RD = 1;
    
    _CS = 1; // toggle CS to interupt the cmd in case was not supported
    _CS = 0;

    _port.output();
    return r;
}
// in Par mode EXTC regs (0xB0-0xFF) can be directly read
unsigned int PAR16::rd_extcreg_data32(unsigned char reg, unsigned char SPIreadenablecmd)
{
    return rd_reg_data32(reg);
}
// ILI932x specific
void PAR16::dummyread()
{
    _port.input();
    _RD = 0;
    _port.read();    // dummy read
    _RD=1;
 //   _port.output();
}
// ILI932x specific
void PAR16::reg_select(unsigned char reg, bool forread)
{    
    _DC = 0;
    _port.write(reg);    // write 16bit
    _WR=0;
    _WR=1;
    _DC = 1; // 1=data next
}
// ILI932x specific
void PAR16::reg_write(unsigned char reg, unsigned short data)
{
    _DC = 0;
    _port.write(reg);    // write 16bit
    _WR=0;
    _WR=1;
    _DC = 1;
    _port.write(data);    // write 16bit
    _WR=0;
    _WR=1;
}
// ILI932x specific
unsigned short PAR16::reg_read(unsigned char reg)
{
    unsigned short r=0;
    _DC = 0;
    _port.write(reg);    // write 16bit
    _WR=0;
    _WR=1;
    _DC = 1;
    _port.input();
    _RD=0;
    r |= _port.read();    // read 16bit
    _RD=1;
    _port.output();
    return r;
}
void PAR16::hw_reset()
{
    ThisThread::sleep_for(15);
    _DC = 1;
    _CS = 1;
    _WR = 1;
    _RD = 1;
    _reset = 0;                        // display reset
    ThisThread::sleep_for(2);
    _reset = 1;                       // end reset
    ThisThread::sleep_for(100);
}
void PAR16::BusEnable(bool enable)
{
    _CS = enable ? 0:1;
}

#endif