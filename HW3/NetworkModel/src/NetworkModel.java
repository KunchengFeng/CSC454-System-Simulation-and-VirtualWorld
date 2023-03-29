public class NetworkModel {
    XOR xor1, xor2;
    Memory memory;

    public NetworkModel(int xor1_state, int xor2_state, int memory_state_1, int memory_state_2) {
        this.xor1 = new XOR((byte) xor1_state);
        this.xor2 = new XOR((byte) xor2_state);
        this.memory = new Memory((byte) memory_state_1, (byte) memory_state_2);
    }

    public void lambda() {
        System.out.println("Output: " + xor2.lambda());
    }

    public void coupling(byte input1, byte input2) {
        memory.write(xor2.coupling(xor1.coupling(input1, input2), memory.read()));
    }

    public void delta() {
        xor1.delta();
        xor2.delta();
        memory.delta();
    }

    public void printState() {
        System.out.println("{ Xor1: " + xor1.state + ", Xor2: " + xor2.state + ", Memory: ("
        + memory.q1 + ", " + memory.q2 + ") }");
    }
}
