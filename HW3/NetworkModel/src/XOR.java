public class XOR {
    byte input1, input2, state;

    public XOR(byte state) {
        this.state = state;
    }

    public byte lambda() {
        return state;
    }

    public byte coupling(byte input1, byte input2) {
        this.input1 = input1;
        this.input2 = input2;
        return state;
    }

    public void delta() {
        if (input1 == input2) {
            state = 0;
        } else {
            state = 1;
        }
    }
}
