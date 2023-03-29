#include <iostream>
#include <string>
using namespace std;

class AtomicModel {
private:
	int quarters, dimes, nickels, value;
	bool change;

public:
	AtomicModel(int quarters, int dimes, int nickels, int value, bool change) {
		this->quarters = quarters;
		this->dimes = dimes;
		this->nickels = nickels;
		this->value = value;
		this->change = change;
	}

	void lambda() {
		int tempV = value;

		if (change) {
			int tempQ = quarters;
			int tempD = dimes;
			int tempN = nickels;

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
					throw string("\nError, no sufficient coins for an exact change.");
				}
			}
		}
		else {while (tempV >= 100) {tempV -= 100; cout << "coffee ";}}
		cout << "\n";
	}

	void delta(string input) {

		if (change) {

			while (value > 0) {
				if (value >= 25 && quarters > 0) {
					value -= 25;
					quarters--;
				}
				else if (value >= 10 && dimes > 0) {
					value -= 10;
					dimes--;
				}
				else if (value >= 5 && nickels > 0) {
					value -= 5;
					nickels--;
				}
				else {
					throw string("Error, no sufficient coins for an exact change.");
				}
			}
			change = false;
		}
		else {while (value >= 100) {value -= 100;}}

		for (int i = 0; i < input.length(); i++) {

			if (input[i] == 'q') {
				value += 25;
				quarters++;
			}
			else if (input[i] == 'd') {
				value += 10;
				dimes++;
			}
			else if (input[i] == 'n') {
				value += 5;
				nickels++;
			}
			else if (input[i] == 'c') {
				change = true;
			}
			else if (input[i] == 'w') {
				try {
					this->lambda();
					if (i == input.length() - 1) {
						this->delta("");
					}
					else {
						this->delta(input.substr(i + 1));
						break;
					}
				}
				catch (string message) {
					cout << message << endl;
					exit(1);
				}
			}
			else {
				cout << "Error, unknown input" << endl;
				return;
			}
		}
	}

	void printState() {
		cout << "{ quarters: " << quarters << ", dimes: " << dimes << ", nickels: " << nickels << ", value: " << value << ", change: ";
		if (change) { cout << "true }" << endl; }
		else { cout << "false }" << endl; }
	}
};
