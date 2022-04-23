
#include "pcf8574.h"

#include "config/pins_config.h"

#include "globals.h"

I2C _i2c(EXP_I2C_SDA, EXP_I2C_SCL ); // (sda,scl)

PCF8574 pcf0(&_i2c, 0x00, PCF8574_TYPE);

PCF8574 pcf1(&_i2c, 0x01, PCF8574_TYPE);

PCF8574 pcf2(&_i2c, 0x02, PCF8574_TYPE);

PCF8574 pcf3(&_i2c, 0x03, PCF8574_TYPE);

PCF8574 pcf4(&_i2c, 0x04, PCF8574_TYPE);

Mutex function_mutex;


void manualValves() 
{

    unsigned int data, binary,shift;
    
    function_mutex.lock();

    // 0-7
    data = 0b00000000;

    shift = 0;

    for (int i = 0; i < 8; i++) 
    {

        if (manual_valves[i] == 0) 
        {

            binary = 0b00000000;
            
        } 
        else 
        {

            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf0.WriteByte(~data);

    // 8-15
    data = 0b00000000;

    shift = 0;

    for (int i = 8; i < 16; i++) 
    {
        if (manual_valves[i] == 0) 
        {

            binary = 0b00000000;
        } 
        else 
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf1.WriteByte(~data);
    // 16-23
    data = 0b00000000;

    shift = 0;

    for (int i = 16; i < 24; i++) 
    {
        if (manual_valves[i] == 0) 
        {
            binary = 0b00000000;
        } 
        else
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf2.WriteByte(~data);
    // 24-31
    data = 0b00000000;

    shift = 0;

    for (int i = 24; i < 32; i++)
     {
        if (manual_valves[i] == 0) 
        {
            binary = 0b00000000;
        } 
        else 
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf3.WriteByte(~data);
    // 32-39

    data = 0b00000000;

    shift = 0;

    for (int i = 32; i < 40; i++) 
    {
        if (manual_valves[i] == 0) 
        {
            binary = 0b00000000;
        } 
        else 
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf4.WriteByte(~data);

    function_mutex.unlock();
    
}

void autoValves() 
{

    unsigned int data, binary;

    int shift;
    
    function_mutex.lock();

    data = 0b00000000;

    shift = 0;

    for (int i = 0; i < 8; i++) 
    {
      if (auto_valves[i] == 0) 
      {
          binary = 0b00000000;
      } 
      else 
      {
          binary = 0b00000001;
      }

      binary = binary << shift;

      data = data | binary;

      shift++;
    }

    pcf0.WriteByte(data);

    data = 0b00000000;

    shift = 0;

    for (int i = 8; i < 16; i++) 
    {
        if (auto_valves[i] == 0)
        {
            binary = 0b00000000;
        } 
        else 
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf1.WriteByte(data);

    data = 0b00000000;

    shift = 0;

    for (int i = 16; i < 24; i++) 
    {

        if (auto_valves[i] == 0) 
        {
            binary = 0b00000000;
        } 
        else 
        {
            binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;

    }

    pcf2.WriteByte(data);

    data = 0b00000000;

    shift = 0;

    for (int i = 24; i < 32; i++) 
    {
        if (auto_valves[i] == 0) 
        {
            binary = 0b00000000;
        }
        else 
        {
          binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
        
    }
    
    pcf3.WriteByte(data);

    data = 0b00000000;

    shift = 0;

    for (int i = 32; i < 40; i++) 
    {
        if (auto_valves[i] == 0) 
        {
          binary = 0b00000000;
        } 
        else 
        {
          binary = 0b00000001;
        }

        binary = binary << shift;

        data = data | binary;

        shift++;
    }

    pcf4.WriteByte(data);

    function_mutex.unlock();
    
}

void closeValves() 
{
  
  function_mutex.lock();

  pcf0.WriteByte(0x00);

  pcf1.WriteByte(0x00);

  pcf2.WriteByte(0x00);

  pcf3.WriteByte(0x00);

  pcf4.WriteByte(0x00);

  function_mutex.unlock();
  
}