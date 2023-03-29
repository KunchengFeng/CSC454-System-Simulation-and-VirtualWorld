import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        String input;
        byte b, a = (byte) 0;
        boolean ready = false;
        NetworkModel model = new NetworkModel(0, 0, 0, 0);
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to the network model.");

        while (true) {
            input = scanner.next();

            if (input.equalsIgnoreCase("exit")) {
                break;
            } else {

                for (int i = 0; i < input.length(); i++) {
                    if (input.charAt(i) == '0' || input.charAt(i) == '1') {
                        if (!ready) {
                            a = (byte) input.charAt(i);
                            ready = true;
                        } else {
                            b = (byte) input.charAt(i);
                            ready = false;
                            for (int j = 0; j < 3; j++) {
                                model.lambda();
                                model.coupling(a, b);
                                model.delta();
                                model.printState();
                            }
                        }
                    }
                }
            }
        }

        System.out.println("Goodbye.");
    }
}
