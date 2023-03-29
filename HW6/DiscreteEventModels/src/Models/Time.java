package Models;

/* Note: The ordering imposed by Models.Time.compareTo is not consistent with equals! */
public class Time implements Comparable<Time> {
    public final double r;
    public final int c;

    public Time(double r, int c) {
        this.r = r;
        this.c = c;
    }

    public Time advance(double increment) {
        if (increment == 0.00) {
            return new Time(r, c + 1);
        } else {
            return new Time(r + increment, 0);
        }
    }

    @Override
    public int compareTo(Time other) {
        final int comparison = Double.compare(r, other.r);
        if (comparison < 0) {
            return -1;
        } else if (comparison > 0) {
            return 1;
        } else {
            return Integer.compare(c, other.c);
        }
    }

    public double elapsed(Time other) {
        return r - other.r;
    }

    public boolean equals(Time other) {
        return this.compareTo(other) == 0;
    }

    public void printState() {
        System.out.print(r + "," + c);
    }
}
