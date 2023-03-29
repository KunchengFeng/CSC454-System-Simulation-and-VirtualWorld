package AtomicModels;

import Models.Event;
import Models.Time;

public abstract class AtomicModel<InputType, OutputType> {
    // Debugging purposes
    public String name;
    public abstract void printState();

    // Used to keep track of overlapping invalid events
    private Event scheduled;
    public Event getScheduled() {return scheduled;}
    public void setScheduled(Event event) {scheduled = event;}

    // Functions
    public abstract double timeAdvance();
    public abstract OutputType lambda();
    public abstract void deltaInternal(Time time);
    public abstract void deltaExternal(Time time, InputType input);
    public abstract void deltaConfluent(Time time, InputType input);
}
