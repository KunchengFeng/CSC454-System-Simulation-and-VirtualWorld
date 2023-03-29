package AtomicModels;

import Models.Queue;
import Models.Time;

public class Memory extends AtomicModel<Integer, Integer> {
    private final Queue<Integer> queue;
    private final double jobTime;
    private double remain;
    private Time time;

    public Memory(double jobTime) {
        this.jobTime = jobTime;
        queue = new Queue<>();
        queue.enqueue(0);
        queue.enqueue(0);
        remain = jobTime;
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
    public Integer lambda() {return queue.peak();}

    @Override
    public void deltaInternal(Time newTime) {
        queue.dequeue();
        time = newTime;
    }

    @Override
    public void deltaExternal(Time newTime, Integer input) {
        remain = jobTime;
        queue.enqueue(input);
        time = newTime;
    }

    @Override
    public void deltaConfluent(Time newTime, Integer input) {
        queue.dequeue();
        remain = jobTime;
        queue.enqueue(input);
        time = newTime;
    }

    @Override
    public void printState() {
        System.out.print("Queue:");
        for (int i = 0; i < queue.count(); i++) {
            System.out.print(" " + queue.peak(i));
        }
    }
}
