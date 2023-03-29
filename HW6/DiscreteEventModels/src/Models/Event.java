package Models;

import AtomicModels.AtomicModel;

/* Note: The ordering imposed by Models.Event.compareTo is not consistent with equals! */
public class Event implements Comparable<Event> {
    public final AtomicModel<Integer, Integer> model;
    public final Time time;
    public final String type;
    public final int value;

    public Event(Time moment, AtomicModel<Integer, Integer> model, String type, int value) {
        time = moment;
        this.type = type;
        this.model = model;
        this.value = value;
    }

    @Override
    public int compareTo(Event other) {
        int a = this.time.compareTo(other.time);
        if (a < 0) {
            return -1;
        } else if (a > 0) {
            return 1;
        } else {
            if (other.model == this.model) {
                return 0;
            } else {
                return -1;
            }
        }
    }
}
