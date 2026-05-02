#ifndef EVENT_QUEUE_CONTROLLER_H
#define EVENT_QUEUE_CONTROLLER_H

#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <bits/stdc++.h>
#include <mutex>
#include <queue>
#include <string>

using namespace std;

class EventQueueController {
   public:
      void push(string add_to_queue);
      void pop();
      string front();
      string back();
      bool empty();
      void print();
      void add_dummy_items();
   
   private:
      queue<string> event_queue;
      std::mutex event_queue_mutex;
};

#endif
