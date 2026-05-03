#include "Embedded_RPi_Demo.h"

#include <wiringPiI2C.h>
#include <wiringPiSPI.h>

using namespace std;

int main()
{
   std::thread run_thread(run); 
   run_thread.join();
   cout << "Exit Condition met. Exiting.." << endl;
   return 0;
}



