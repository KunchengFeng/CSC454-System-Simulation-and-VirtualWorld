#include <iostream>
#include "XOR.h"
#include "Memory.h"

using namespace std;

class NetworkModel {
private:
	XOR* xor1;
	XOR* xor2;
	Memory* memory;

public:
	NetworkModel(int xor1_state, int xor2_state, int memoryState_1, int memoryState_2) {
		xor1 = new XOR(xor1_state);
		xor2 = new XOR(xor2_state);
		memory = new Memory(memoryState_1, memoryState_2);
	}

	void lambda() {
		cout << "Output: " << xor2->lambda() << endl;
	}

	void coupling(int input1, int input2) {
		int a = xor1->coupling(input1, input2);
		int b = memory->read();
		int c = xor2->coupling(a, b);
		memory->write(c);
	}

	void delta() {
		xor1->delta();
		xor2->delta();
		memory->delta();
	}

	void printState() {
		cout << "{ XOR1: " << xor1->lambda() << ", XOR2: " << xor2->lambda() << ", memory: (" << memory->getQ1() << ", " << memory->read() << ") }" << endl;
	}

	void delteComponents() {
		delete xor1;
		delete xor2;
		delete memory;
	}
};