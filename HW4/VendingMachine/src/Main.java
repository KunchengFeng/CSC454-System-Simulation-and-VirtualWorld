import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        VendingMachine machine = new VendingMachine(0, 0, 0, 0);
        EventQueue events = new EventQueue();
        Event scheduled = new Event(0.00, "nothing");
        Event current;

        try {
            File file = new File("Inputs[1].txt");
            Scanner scanner = new Scanner(file);

            while (scanner.hasNextLine()) {
                events.enqueue(scanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error, cannot read file.");
            System.exit(1);
        }

        // Time advance
        while (events.hasNext()) {
            current = events.dequeue();

            // Possible tasks include: {change, q, d, n}.
            if (scheduled.task.equalsIgnoreCase("nothing")) {
                machine.deltaExternal(current.task);
                scheduled.time = current.time + 2;
                scheduled.task = "change";
            } else {
                if (current.time < scheduled.time) {
                    machine.deltaExternal(current.task);
                    scheduled.time = current.time + 2;
                    scheduled.task = "change";
                } else if (current.time > scheduled.time) {
                    try {
                        // Scheduled event
                        System.out.print(scheduled.time + "s: ");
                        machine.lambda();
                        machine.deltaInternal();
                        // Current event
                        machine.deltaExternal(current.task);
                        scheduled.time = current.time + 2;
                        scheduled.task = "change";
                    } catch (NoChangeException exception) {
                        System.out.println(exception.getMessage());
                        System.exit(1);
                    }
                } else {
                    System.out.print(current.time + "s: ");
                    machine.deltaConfluent(current.task);
                    scheduled.time = current.time + 2;
                    scheduled.task = "change";
                }
            }
        }

        // Last scheduled event
        if (scheduled.task.equalsIgnoreCase("change")) {
            try {
                System.out.print(scheduled.time + "s: ");
                machine.lambda();
                machine.deltaInternal();
            } catch (NoChangeException exception) {
                System.out.println(exception.getMessage());
                System.exit(1);
            }
        }

        System.out.println("Goodbye.");
    }
}
