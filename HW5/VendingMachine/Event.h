#include <string>
#pragma once

class Event {
public:
	double time;
	std::string task;
	Event* next;

	Event(double time, std::string task) {
		this->time = time;
		this->task = task;
	}
};