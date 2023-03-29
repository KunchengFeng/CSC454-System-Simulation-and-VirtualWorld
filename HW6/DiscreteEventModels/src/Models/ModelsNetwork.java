package Models;

import Couplings.*;
import java.util.ArrayList;

public class ModelsNetwork {
    private final ArrayList<CouplingModel> couplings;
    private final CouplingOutput couplingOutput;

    public ModelsNetwork(CouplingOutput outputCoupling, int numOfCouplings) {
        couplingOutput = outputCoupling;
        couplings = new ArrayList<>(numOfCouplings);
    }

    public void addCoupling(CouplingModel couplingModel) {
        couplings.add(couplingModel);
    }

    public void process(Event event, MinHeap<Event> events) {
        // Line used for event checking
        //whatIsState(event);

        if (event.type.equalsIgnoreCase("input")) {
            event.model.deltaExternal(event.time, event.value);
        } else {
            int output = event.model.lambda();

            if (event.type.equalsIgnoreCase("output")) {
                event.model.deltaInternal(event.time);
            } else {
                event.model.deltaConfluent(event.time, event.value);
            }

            for (CouplingModel couplingModel : couplings) {
                couplingModel.process(event, events, output);
            }
            couplingOutput.process(event, output);
        }

        // Schedule an output event (Conditional)
        double remain = event.model.timeAdvance();
        if (remain != Double.MAX_VALUE) {
            // Remove obsolete event
            Event scheduled = event.model.getScheduled();
            events.remove(scheduled);
            // Schedule a new event
            Time newTime = event.time.advance(remain);
            Event newEvent = new Event(newTime, event.model, "output", 0);
            events.insert(newEvent);
            event.model.setScheduled(newEvent);
        } else {
            event.model.setScheduled(null);
        }

        //whatIsState(event);
    }

    private void whatIsState(Event event) {
        System.out.print("Time: ");
        event.time.printState();

        System.out.print(", Type: " + event.type + ", Value: " + event.value + ", " + event.model.name + ": ");
        event.model.printState();
        System.out.println();
    }
}
