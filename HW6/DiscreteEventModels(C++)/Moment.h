#ifndef MOMENT_HEADER
#define MOMENT_HEADER

#include <iostream>

class Moment {
public:
	double real;
	int discrete;

	Moment(double real, int discrete) {
		this->real = real;
		this->discrete = discrete;
	}

	Moment* advance(double increment) {
		if (increment == 0) {
			return new Moment(real, discrete + 1);
		}
		else {
			return new Moment(real + increment, 0);
		}
	}

	bool operator > (Moment const* other) {
		double difference = this->real - other->real;
		if (difference > 0.01) {
			return true;
		}
		else if (difference < -0.01) {
			return false;
		}
		else {
			if (this->discrete > other->discrete) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool operator < (Moment const* other) {
		double difference = this->real - other->real;
		if (difference < -0.01) {
			return true;
		}
		else if (difference > 0.01) {
			return false;
		}
		else {
			if (this->discrete < other->discrete) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool operator == (Moment const* other) {
		double difference = abs(this->real - other->real);
		if (difference < 0.01) {
			if (this->discrete == other->discrete) {
				return true;
			}
			else { return false; }
		}
		else { return false; }
	}

	void printState() {
		std::cout << real << "," << discrete;
	}
};

#endif