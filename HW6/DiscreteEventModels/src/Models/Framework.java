package Models;

public class Framework {
    public Framework() {}

    public void simulate(ModelsNetwork modelsNetwork, MinHeap<Event> events) {
        while (events.hasNext()) {
            Event event = events.remove();

            // Try to form a confluent event, if successful replace the current event with it.
            Event complementary = events.seek(event);
            if (complementary != null) {
                String type1 = event.type;
                String type2 = complementary.type;
                if ((type1.equalsIgnoreCase("input") && type2.equalsIgnoreCase("output"))
                    || (type1.equalsIgnoreCase("output") && type2.equalsIgnoreCase("input"))) {
                    Event confluent = new Event(event.time, event.model, "confluent", event.value + complementary.value);
                    event.model.setScheduled(confluent);
                    events.remove(complementary);
                    event = confluent;
                }
            }

            modelsNetwork.process(event, events);
        }
    }
}
