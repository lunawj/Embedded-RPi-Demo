#ifndef I2C_DEMO_H
#define I2C_DEMO_H

using namespace std;

#include <iostream>
#include <wiringPi.h>
#include <pcf8591.h>
#include <string.h>
#include <queue>

const int PIN_BASE = 64;
const int ADC_ADDRESS = 0x48;
#define AN0 0
#define AN1 1
#define AN2 2
#define AN3 3
#define AOUT 0

bool setup_i2c_adc();

#endif
