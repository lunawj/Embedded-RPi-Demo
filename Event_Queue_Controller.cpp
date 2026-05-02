#include "Event_Queue_Controller.h"

void EventQueueController::push(string add_to_queue)
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	event_queue.push(add_to_queue);
}
      
void EventQueueController::pop()
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	event_queue.pop();
}
      
string EventQueueController::front()
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	return event_queue.front();
}
      
string EventQueueController::back()
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	return event_queue.back();
}
      
bool EventQueueController::empty()
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	return event_queue.empty();
}
      
void EventQueueController::print()
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
      
void EventQueueController::add_dummy_items()
{
	std::lock_guard event_queue_lock_guard(event_queue_mutex);
	event_queue.push("10");
	event_queue.push("20");
    event_queue.push("30");
    event_queue.push("40");
	event_queue.push("50");
}

