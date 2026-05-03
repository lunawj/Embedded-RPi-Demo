#include "Embedded_RPi_Demo.h"

#include <wiringPiI2C.h>
#include <wiringPiSPI.h>

using namespace std;

int main()
{
   //int adc_fd = wiringPiI2CSetup(0x48);
   //int result = wiringPiI2CWriteReg8(fd, 0x40, (i & 0xfff) );
   
   std::thread run_thread(run); 
   run_thread.join();
   cout << "Exit Condition met. Exiting.." << endl;
   return 0;
}



