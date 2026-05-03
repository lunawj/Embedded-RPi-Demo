#include "i2c_demo.h"

bool setup_i2c_adc()
{
   bool successful_setup = true;
   if(!pcf8591Setup(PIN_BASE, ADC_ADDRESS))
   {
      successful_setup = false;
   }
   return successful_setup;
}



