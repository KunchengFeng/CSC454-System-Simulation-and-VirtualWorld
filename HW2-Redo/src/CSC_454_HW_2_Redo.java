import java.util.Scanner;

public class CSC_454_HW_2_Redo {
    // Class Simulator
    // Coded with java JDK-17 on home device.

    public static void main(String[] args) {
        //create a model;
        String input;
        Scanner scanner = new Scanner(System.in);
        AtomicModel model = new AtomicModel(0,0,0,0,false);

        while (true) {
            input = scanner.nextLine();

            if (input.equalsIgnoreCase("exit")) {
                break;
            } else {
                try {
                    System.out.println(model.lambda());
                    model.delta(input);
                    model.printState();
                } catch (NoChangeException exception) {
                    System.out.println(exception.getMessage());
                    System.exit(1);
                }
            }
        }
        System.out.println("Goodbye.");
    }
}
