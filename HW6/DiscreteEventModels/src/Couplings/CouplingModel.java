package Couplings;

import AtomicModels.AtomicModel;
import Models.Event;
import Models.MinHeap;
import Models.Time;

public class CouplingModel {
    private final AtomicModel<Integer, Integer> source, target;

    public CouplingModel(AtomicModel<Integer, Integer> source, AtomicModel<Integer, Integer> target) {
        this.source = source;
        this.target = target;
    }

    public void process(Event event, MinHeap<Event> events, int output) {
        if (event.model == source
                && (event.type.equalsIgnoreCase("output")
                ||  event.type.equalsIgnoreCase("confluent"))) {
            Time newTime = event.time.advance(0);
            events.insert(new Event(newTime, target, "input", output));
        }
    }
}
