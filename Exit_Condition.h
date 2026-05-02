#ifndef EXIT_CONDITION_H
#define EXIT_CONDITION_H

using namespace std;

#include <iostream>
#include <mutex>

class ExitCondition
{
   public:
      bool is_exit_condition_met();
      void set_exit_condition(bool update);
      
   private:
      bool exit_condition_met = false;
      std::mutex exit_condition_mutex;
};

#endif
