public class EventQueue {
    Event head;

    public EventQueue(){
        head = null;
    }

    public void enqueue(String input) {
        // Inputs should be [Time], [Task]
        double time = Double.parseDouble(input.substring(0, input.indexOf(",")));
        String task = input.substring(input.indexOf(",")+2);
        Event event = new Event(time, task);
        int result;

        if (head != null) {
            result = head.compare(event);
            if (result < 0) {                       // Head comes before the event.
                Event current = head;

                while (true) {
                    if (current.next != null) {
                        result = current.next.compare(event);
                        if (result < 0) {
                            current = current.next;
                        } else {
                            Event temp = current.next;
                            current.next = event;
                            event.next = temp;
                            break;
                        }
                    } else {
                        current.next = event;
                        break;
                    }
                }
            } else {                                // Event comes before the head.
                Event temp = head;
                head = event;
                head.next = temp;
            }

        } else {
            head = event;
        }
    }

    public Event dequeue() {
        Event event = head;
        head = head.next;
        return event;
    }

    public boolean hasNext() {
        return head != null;
    }
}
