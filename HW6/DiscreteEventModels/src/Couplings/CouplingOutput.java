package Couplings;

import AtomicModels.AtomicModel;
import Models.Event;

public class CouplingOutput {
    private final AtomicModel<Integer, Integer> model;

    public CouplingOutput(AtomicModel<Integer, Integer> model) {
        this.model = model;
    }

    public void process(Event event, int output) {
        if (event.model == this.model
                && (event.type.equalsIgnoreCase("output")
                ||  event.type.equalsIgnoreCase("Confluent"))) {
            System.out.println("Time: " + event.time.r + ", " + event.type + ": " + output);
        }
    }
}
