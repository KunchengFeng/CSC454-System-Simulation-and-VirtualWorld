class XOR {
private:
	int state, input1, input2;

public:
	XOR(int state) {
		this->state = state;
		input1 = 0;
		input2 = 0;
	}

	int lambda() {
		return state;
	}

	int coupling(int input1, int input2) {
		this->input1 = input1;
		this->input2 = input2;
		return state;
	}

	void delta() {
		if (input1 == input2) {
			state = 0;
		}
		else {
			state = 1;
		}
	}
};