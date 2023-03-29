public class Memory {
    // input -> q1 -> q2 -> output.
    byte q1, q2, input;

    public Memory(byte state1, byte state2) {
        this.q1 = state1;
        this.q2 = state2;
    }

    public byte read() {
        return q2;
    }

    public void write(byte input) {
        this.input = input;
    }

    public void delta() {
        q2 = q1;
        q1 = input;
    }
}
