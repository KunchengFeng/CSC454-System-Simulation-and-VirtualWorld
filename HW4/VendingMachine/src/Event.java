public class Event {
    double time;
    String task;
    Event next;

    public Event(double time, String task) {
        this.time = time;
        this.task = task;
        next = null;
    }

    public int compare(Event other) {
        return Double.compare(this.time, other.time);
    }
}
