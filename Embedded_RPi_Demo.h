#ifndef EMBEDDED_RPI_DEMO_H
#define EMBEDDED_RPI_DEMO_H


#include "Event_Queue_Controller.h"
#include "Exit_Condition.h"
#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <bits/stdc++.h>
#include <mutex>
#include <queue>
#include <string>

#define QUIT "quit\0"
#define BUTTON_PIN 17

void run();
void get_user_input();
void periodic_event();
string to_lower(string input_str);
void button_handler();

#endif
