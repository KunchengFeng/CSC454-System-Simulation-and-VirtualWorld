#pragma once
#include <PressDrillModel.h>
#include <Moment.h>
#include <string.h>
using namespace std;

class Event {
public:
	PressDrillModel* model;
	Moment* moment;
	string kind;
	int value;

	Event() {
		model = NULL;
		moment = NULL;
		kind = "Unknown";
		value = 0;
	}

	Event(Moment* moment, PressDrillModel* model, string kind, int value) {
		this->moment = moment;
		this->model = model;
		this->kind = kind;
		this->value = value;
	}

	bool operator > (Event const* other) {
		return (this->moment > other->moment);
	}

	bool operator < (Event const* other) {
		return (this->moment < other->moment);
	}

	bool operator == (Event const* other) {
		if (this->moment == other->moment) {
			if (this->model == other->model) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	bool operator != (Event const* other) {
		return !(this == other);
	}
};