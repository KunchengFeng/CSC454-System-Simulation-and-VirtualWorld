package com.company;

import java.util.Scanner;

public class Main {

    private static void help() {
        System.out.println("Available commands include {n, d, q, c, w, help, exit}");
    }

    private static void lambda(VendingMachine machine){
        // Check if any changes are needed.
        try {
            machine.changeLambda();
        } catch (NoChangeException nce) {
            System.out.println("Exception occurred: " + nce);
            System.exit(0);
        }

        // Dispense any available coffee, the rest are state change which are handled in delta function.
        machine.dispenseLambda();
    }

    private static void delta(String input, VendingMachine machine){
        try {
            machine.changeDelta();
        } catch (NoChangeException nce){
            System.out.println("Exception occurred: " + nce);
            System.exit(0);
        }

        machine.dispenseDelta();

        // React to each letter of the input.
        char c;
        for (int i = 0; i < input.length(); i++){
            c = input.charAt(i);
            switch (c) {
                case 'q' -> machine.insertCoin("quarter");
                case 'd' -> machine.insertCoin("dime");
                case 'n' -> machine.insertCoin("nickel");
                case 'c' -> machine.setChange();
                default -> {
                    System.out.println("Error, unknown input");
                    return;
                }
            }
        }
    }

    private static void process(String input, VendingMachine machine){
        // Each time lambda and delta is called, it's a tick.

        // Check for wait.
        char c;
        for (int i = 0; i < input.length(); i++){
            c = input.charAt(i);
            switch(c) {
                case 'q':
                case 'd':
                case 'n':
                case 'c':
                    continue;
                case 'w': {
                    lambda(machine);
                    delta(input.substring(0, i), machine);

                    if (i == input.length()-1){
                        lambda(machine);
                        delta("", machine);
                    } else {
                        process(input.substring(i+1), machine);
                    }
                    return;
                }
                default:
                    System.out.println("Error, unknown input.");
                    return;
            }
        }

        // No waits needed, call function
        lambda(machine);
        delta(input, machine);
    }

    public static void main(String[] args) {
        VendingMachine machine = new VendingMachine(0,0,0,0,false);
	    Scanner scanner = new Scanner(System.in);
	    String input;

        System.out.println("Welcome to the vending machine.");
	    while (true){
	        input = scanner.nextLine();
	        if (input.equals("exit")){
                break;
            } else if (input.equals("help")){
                help();
            } else {
	            // Quick check for unknown input.
                char c;
                boolean error = false;

                for (int i = 0; i < input.length(); i++){
                    c = input.charAt(i);
                    switch(c) {
                        case 'q':
                        case 'd':
                        case 'n':
                        case 'c':
                        case 'w':
                            continue;
                        default: error = true;
                    }
                }

                if (error){
                    System.out.println("Error, unknown input.");
                } else {
                    process(input, machine);
                    machine.printState();
                }
            }
        }
	    System.out.println("Goodbye.");
    }
}
