import AtomicModels.*;
import Couplings.*;
import Models.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("\n\nHomework 3 Starts Here:\n");
        homework3();

        System.out.println("\n\nHomework 5 Starts Here:\n");
        homework5();
    }

    private static void homework5() {
        // Set up framework's basic components.
        Press press = new Press();
        Drill drill = new Drill();
        CouplingModel couplingModel = new CouplingModel(press, drill);
        CouplingOutput couplingOutput = new CouplingOutput(drill);
        ModelsNetwork modelsNetwork = new ModelsNetwork(couplingOutput, 1);
        modelsNetwork.addCoupling(couplingModel);
        Framework framework = new Framework();
        MinHeap<Event> events = new MinHeap<>(100);

        // Debugging purposes
        press.name = "Press";
        drill.name = "Drill";

        // Initialize events for the framework.
        try {
            File file = new File("Press_Drill_Inputs[0].txt");
            Scanner scanner = new Scanner(file);

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                int comma = line.indexOf(",");
                int space = line.indexOf(" ");
                double real = Double.parseDouble(line.substring(0, comma));
                int discrete = Integer.parseInt(line.substring(comma + 1, space));
                int value = Integer.parseInt(line.substring(space + 1));

                Time time = new Time(real, discrete);
                Event event = new Event(time, press, "input", value);
                events.insert(event);
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error: could not open file.");
            System.exit(1);
        }

        // Simulates it
        framework.simulate(modelsNetwork, events);
    }

    private static void homework3() {
        // Set up the framework
        XOR xor1 = new XOR(1, 0);
        XOR xor2 = new XOR(1, 0);
        Memory memory = new Memory(0);
        CouplingModel xor1ToXor2 = new CouplingModel(xor1, xor2);
        CouplingModel memoryToXor2 = new CouplingModel(memory, xor2);
        CouplingModel xor2ToMemory = new CouplingModel(xor2, memory);
        CouplingOutput output = new CouplingOutput(xor2);
        ModelsNetwork network = new ModelsNetwork(output, 3);
        network.addCoupling(xor1ToXor2);
        network.addCoupling(memoryToXor2);
        network.addCoupling(xor2ToMemory);
        Framework framework = new Framework();
        MinHeap<Event> events = new MinHeap<>(100);

        // Debugging purposes
        xor1.name = "XOR1";
        xor2.name = "XOR2";
        memory.name = "Memory";

        // Initialize events for the framework.
        try {
            File file = new File("Network_Inputs[0].txt");
            Scanner scanner = new Scanner(file);

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                int comma = line.indexOf(",");
                int space = line.indexOf(" ");
                double real = Double.parseDouble(line.substring(0, comma));
                int discrete = Integer.parseInt(line.substring(comma + 1, space));
                String input = line.substring(space + 1);

                Time time = new Time(real, discrete);
                for (int a = 0; a < input.length(); a++) {
                    Event event = new Event(time, xor1, "input", Integer.parseInt(String.valueOf(input.charAt(a))));
                    events.insert(event);
                }
            }

            // Manual initialization to get the network moving in natural order
            Time startTime = new Time(0, 0);
            Event memory_Output = new Event(startTime, memory, "output", 0);
            events.insert(memory_Output);

        } catch (FileNotFoundException e) {
            System.out.println("Error: could not open file.");
            System.exit(1);
        }

        // Simulates it
        framework.simulate(network, events);
    }
}
