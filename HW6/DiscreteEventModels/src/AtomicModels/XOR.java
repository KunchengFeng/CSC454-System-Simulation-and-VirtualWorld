package AtomicModels;

import Models.Queue;
import Models.Time;

public class XOR extends AtomicModel<Integer, Integer> {
    private int state;
    private final Queue<Integer> queue;
    private final double jobTime;
    private double remain;
    private Time time;

    public XOR(double jobTime, int state) {
        this.jobTime = jobTime;
        queue = new Queue<>();
        this.state = state;
    }

    @Override
    public double timeAdvance() {
        if (queue.count() >= 2) {
            return remain;
        } else {
            return Double.MAX_VALUE;
        }
    }

    @Override
    public Integer lambda() {return state;}

    @Override
    public void deltaInternal(Time newTime) {
        if (queue.count() >= 2) {
            int input1 = queue.dequeue();
            int input2 = queue.dequeue();

            if (input1 == input2) {
                state = 0;
            } else {
                state = 1;
            }

            remain = jobTime;
            time = newTime;
        }
    }

    @Override
    public void deltaExternal(Time newTime, Integer input) {
        if (queue.count() < 2) {
            remain = jobTime;
        } else {
            remain = remain - (newTime.r - time.r);
        }
        queue.enqueue(input);
        time = newTime;
    }

    @Override
    public void deltaConfluent(Time newTime, Integer input) {
        deltaInternal(newTime);
        queue.enqueue(input);
    }

    @Override
    public void printState() {
        System.out.print("State: " + state + ", Queue:");
        for (int i = 0; i < queue.count(); i++) {
            System.out.print(" " + queue.peak(i));
        }
    }
}
