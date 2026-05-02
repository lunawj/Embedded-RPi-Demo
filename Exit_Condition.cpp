#include "Exit_Condition.h"

bool ExitCondition::is_exit_condition_met()
{
	return exit_condition_met;
}
      
void ExitCondition::set_exit_condition(bool update)
{
	std::lock_guard exit_condition_lock_guard(exit_condition_mutex);
	exit_condition_met = update;
}
