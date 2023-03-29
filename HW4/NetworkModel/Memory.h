class Memory {
private:
	// input -> q1 -> q2 -> output.
	int input, q1, q2;

public:
	Memory(int q1, int q2) {
		this->q1 = q1;
		this->q2 = q2;
		input = 0;
	}

	int getQ1() {
		return q1;
	}

	int read() {
		return q2;
	}

	void write(int input) {
		this->input = input;
	}

	void delta() {
		q2 = q1;
		q1 = input;
	}
};