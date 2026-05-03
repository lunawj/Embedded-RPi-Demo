#include "Embedded_RPi_Demo.h"

EventQueueController outboundEventQueue;
EventQueueController inboundEventQueue;
ExitCondition exitCondition;

void run()
{
   wiringPiSetupGpio();
   pinMode(BUTTON_PIN, INPUT);
   
   std::thread periodic_event_thread(periodic_event); 
   std::thread get_user_input_thread(get_user_input); 
   std::thread button_handler_thread(button_handler); 
   std::thread i2c_potentiometer_handler_thread(i2c_potentiometer_handler); 
   
   string tempNode = "";
   while(!exitCondition.is_exit_condition_met())
   {
      if(!inboundEventQueue.empty())
      {
         cout << "Event: " << inboundEventQueue.front() << endl;
         
         tempNode = inboundEventQueue.front();
         tempNode = to_lower(tempNode);
         //cout << "tempNode: " << tempNode << endl;
         
         if(tempNode.compare(QUIT) == 0)
         {
            exitCondition.set_exit_condition(true);
         }
         
         inboundEventQueue.pop();
      }
   }
   
   periodic_event_thread.join();
   get_user_input_thread.join();
   button_handler_thread.join();
   i2c_potentiometer_handler_thread.join(); 
}

void get_user_input()
{
   int seconds_between_events = 1;
   while (!exitCondition.is_exit_condition_met())
   {
      string user_input;
      cin >> user_input;
      inboundEventQueue.push(user_input);
      this_thread::sleep_for(chrono::seconds(seconds_between_events));
   }
}

void periodic_event()
{
   int seconds_between_events = 1;
   int events_sent = 0;
   while (!exitCondition.is_exit_condition_met())
   {
      events_sent++;
      inboundEventQueue.push(to_string(events_sent));
      this_thread::sleep_for(chrono::seconds(seconds_between_events));
   }
}

string to_lower(string input_str)
{
   for_each(input_str.begin(), input_str.end(), [](char& c) {
        c = tolower(c);
    });
    
    return input_str;
}

void button_handler()
{
   int prev_button_state = LOW;
   int current_button_state = digitalRead(BUTTON_PIN);
   int debounce_time = 1;
   
   while (!exitCondition.is_exit_condition_met())
   {
      current_button_state = digitalRead(BUTTON_PIN);
      if(current_button_state != prev_button_state)
      {
         if(current_button_state == HIGH)
         {
            inboundEventQueue.push("Button not pressed");
         }else if(current_button_state == LOW)
         {
            inboundEventQueue.push("Button pressed");
         }
         
         prev_button_state = current_button_state;
      }
      
      this_thread::sleep_for(chrono::seconds(debounce_time));
   }
}

void i2c_potentiometer_handler()
{
   int seconds_between_events = 1;
   if(!setup_i2c_adc())
   {
      cout << "I2C ADC setup unsuccessful. Exiting... " << endl;
      return;
   } 
   
   wiringPiNodeStruct *pcf8591_node = wiringPiNodes;
   int read_value;
   while(!exitCondition.is_exit_condition_met())
   {
      read_value = pcf8591_node->analogRead(pcf8591_node, AN1);
      inboundEventQueue.push("Potentiometer ADC Value: " + to_string(read_value));
      this_thread::sleep_for(chrono::seconds(seconds_between_events));
   }
}
