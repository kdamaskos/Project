
#include <utilities/include/graphics.h>

#include <stdint.h>


static const uint16_t image_data_temp_icon[2000] = {
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 
    BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C, BACKGROUND_C
};


