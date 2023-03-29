#ifndef PRESSDRILLMODEL_HEADER
#define PRESSDRILLMODEL_HEADER

#include <Moment.h>
#include <iostream>

class PressDrillModel {
private:
	int parts;
	double remain;
	double jobTime;
	Moment* time;

public:
	PressDrillModel(double jobTime) { 
		this->jobTime = jobTime; 
		parts = 0;
		remain = 0;
		time = NULL;
	}
	
	double timeAdvance() {
		if (parts > 0) {
			return remain;
		}
		else {
			return 1000000;
		}
	}

	int lambda() {return 1;}

	void deltaInternal(Moment* newTime) {
		if (parts > 0) {
			parts--;
			remain = jobTime;
			time = newTime;
		}
	}

	void deltaExternal(Moment* newTime, int newParts) {
		if (parts == 0) {
			remain = jobTime;
		}
		else {
			remain = remain - (newTime->real - time->real);
		}
		parts += newParts;
		time = newTime;
	}

	void deltaConfluent(Moment* newTime, int newParts) {
		parts += newParts - 1;
		remain = jobTime;
		time = newTime;
	}

	void printState() {
		std::cout << "Parts " << parts << ", Remain: " << remain;
	}
};

#endif