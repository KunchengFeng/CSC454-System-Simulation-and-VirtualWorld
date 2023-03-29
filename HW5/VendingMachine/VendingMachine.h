#include <string>
#include <iostream>
#pragma once
using namespace std;

class VendingMachine {
private:
	int quarters, dimes, nickels, value;

public:
	VendingMachine(int quarters, int dimes, int nickels, int value) {
		this->quarters = quarters;
		this->dimes = dimes;
		this->nickels = nickels;
		this->value = value;
	}

	void lambda() {
		int tempV = value;
		int tempQ = quarters;
		int tempD = dimes;
		int tempN = nickels;

		while (tempV >= 100) {
			tempV -= 100;
			cout << "Coffee ";
		}

		while (tempV > 0) {
			if (tempV >= 25 && tempQ > 0) {
				tempV -= 25;
				tempQ--;
				cout << "quarter ";
			}
			else if (tempV >= 10 && tempD > 0) {
				tempV -= 10;
				tempD--;
				cout << "dime ";
			}
			else if (tempV >= 5 && tempN > 0) {
				tempV -= 5;
				tempN--;
				cout << "nickel ";
			}
			else {
				throw "Error, insufficient coins for exact change.";
			}
		}

		cout << endl;
	}

	void deltaInternal() {
		while (value >= 100) {
			value -= 100;
		}

		while (value > 0) {
			if (value >= 25 && quarters > 0) {
				value -= 25;
				quarters--;
			}
			else if (value >= 10 && dimes > 0) {
				value -= 10;
				dimes--;
			}
			else if (value > 5 && nickels > 0) {
				value -= 5;
				nickels--;
			}
			else {
				throw "Error, insufficient coins for exact change.";
			}
		}
	}

	void deltaExternal(string input) {
		if (input.at(0) == 'q') {
			value += 25;
			quarters++;
		}
		else if (input.at(0) == 'd') {
			value += 10;
			dimes++;
		}
		else if (input.at(0) == 'n') {
			value += 5;
			nickels++;
		}
		else {
			cout << "Error, invalid input.";
		}
	}

	void deltaConfluent(string input) {
		try {
			lambda();
			deltaInternal();
			deltaExternal(input);
		}
		catch (string message) {
			cout << message << endl;
		}
	}
};