#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define QUIT "quit\0"
#define BUTTON_PIN 17

class EventQueueController {
   public:
      void push(string add_to_queue)
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         event_queue.push(add_to_queue);
      }
      
      void pop()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         event_queue.pop();
      }
      
      string front()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         return event_queue.front();
      }
      
      string back()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         return event_queue.back();
      }
      
      bool empty()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         return event_queue.empty();
      }
      
      void print()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         queue<string> temp_event_queue;
         while(!event_queue.empty())
         {
            cout << event_queue.front() << " ";
            temp_event_queue.push(event_queue.front());
            event_queue.pop();
         }
         
         while(!temp_event_queue.empty())
         {
            event_queue.push(temp_event_queue.front());
            temp_event_queue.pop();
         }
         
         cout << endl;
      }
      
      void add_dummy_items()
      {
         std::lock_guard event_queue_lock_guard(event_queue_mutex);
         event_queue.push("10");
         event_queue.push("20");
         event_queue.push("30");
         event_queue.push("40");
         event_queue.push("50");
      }
   
   private:
      queue<string> event_queue;
      std::mutex event_queue_mutex;
};

class ExitCondition
{
   public:
      bool is_exit_condition_met()
      {
         return exit_condition_met;
      }
      
      void set_exit_condition(bool update)
      {
         std::lock_guard exit_condition_lock_guard(exit_condition_mutex);
         exit_condition_met = update;
      }
      
   private:
      bool exit_condition_met = false;
      std::mutex exit_condition_mutex;
};
   
void run();
void get_user_input();
void periodic_event();
string to_lower(string input_str);
void button_handler();


EventQueueController eventQueueController;
ExitCondition exitCondition;



int main()
{
   std::thread run_thread(run); 
   run_thread.join();
   cout << "Exit Condition met. Exiting.." << endl;
   return 0;
}

void run()
{
   wiringPiSetupGpio();
   pinMode(BUTTON_PIN, INPUT);
   
   
   std::thread periodic_event_thread(periodic_event); 
   std::thread get_user_input_thread(get_user_input); 
   std::thread button_handler_thread(button_handler); 
   string tempNode = "";
   while(!exitCondition.is_exit_condition_met())
   {
      if(!eventQueueController.empty())
      {
         cout << "Event: " << eventQueueController.front() << endl;
         
         tempNode = eventQueueController.front();
         tempNode = to_lower(tempNode);
         //cout << "tempNode: " << tempNode << endl;
         
         if(tempNode.compare(QUIT) == 0)
         {
            exitCondition.set_exit_condition(true);
         }
         
         eventQueueController.pop();
      }
   }
   
   periodic_event_thread.join();
   get_user_input_thread.join();
   button_handler_thread.join();
}


void get_user_input()
{
   int seconds_between_events = 1;
   while (!exitCondition.is_exit_condition_met())
   {
      string user_input;
      cin >> user_input;
      eventQueueController.push(user_input);
      this_thread::sleep_for(chrono::seconds(seconds_between_events));
   }
}

void periodic_event()
{
   int seconds_between_events = 5;
   int events_sent = 0;
   while (!exitCondition.is_exit_condition_met())
   {
      events_sent++;
      eventQueueController.push(to_string(events_sent));
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
            eventQueueController.push("Button not pressed");
         }else if(current_button_state == LOW)
         {
            eventQueueController.push("Button pressed");
         }
         
         prev_button_state = current_button_state;
      }
      
      this_thread::sleep_for(chrono::seconds(debounce_time));
   }
}


