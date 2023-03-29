package AtomicModels;

import Models.Time;

public abstract class PressDrillModel extends AtomicModel<Integer, Integer> {
    private int parts;
    private double remain;
    private final double jobTime;
    private Time time;

    public PressDrillModel(double jobTime) {this.jobTime = jobTime;}

    @Override
    public Integer lambda() {return 1;}

    @Override
    public double timeAdvance() {
        if (parts > 0) {
            return remain;
        } else {
            return Double.MAX_VALUE;
        }
    }

    @Override
    public void deltaInternal(Time newTime) {
        if (parts > 0) {
            parts--;
            remain = jobTime;
            time = newTime;
        }
    }

    @Override
    public void deltaExternal(Time newTime, Integer newParts) {
        if (parts == 0) {
            remain = jobTime;
        } else {
            remain = remain - (newTime.r - time.r);
        }
        parts += newParts;
        time = newTime;
    }

    @Override
    public void deltaConfluent(Time newTime, Integer newParts) {
        parts += newParts - 1;
        remain = jobTime;
        time = newTime;
    }

    @Override
    public void printState() {
        System.out.print("Parts: " + parts + ", Remain: " + remain);
    }
}
