public class VendingMachine {
    int quarters, dimes, nickels, value;

    public VendingMachine(int quarters, int dimes, int nickels, int value) {
        this.quarters = quarters;
        this.dimes = dimes;
        this.nickels = nickels;
        this.value = value;
    }

    public void lambda() throws NoChangeException {
        int tempV = value;
        int tempQ = quarters;
        int tempD = dimes;
        int tempN = nickels;

        while (tempV >= 100) {
            tempV -= 100;
            System.out.print("Coffee ");
        }

        while (tempV > 0) {
            if (tempV >= 25 && tempQ > 0) {
                tempV -= 25;
                tempQ--;
                System.out.print("q ");
            } else if (tempV >= 10 && tempD > 0) {
                tempV -= 10;
                tempD--;
                System.out.print("d ");
            } else if (tempV >= 5 && tempN > 0) {
                tempV -= 5;
                tempN--;
                System.out.print("n ");
            } else {
                throw new NoChangeException("Error, insufficient coins for exact change.");
            }
        }

        System.out.println();
    }

    // Basically a change function
    public void deltaInternal() throws NoChangeException {
        while (value >= 100) {
            value -= 100;
        }

        while (value > 0) {
            if (value >= 25 && quarters > 0) {
                value -= 25;
                quarters--;
            } else if (value >= 10 && dimes > 0) {
                value -= 10;
                dimes--;
            } else if (value > 5 && nickels > 0) {
                value -= 5;
                nickels--;
            } else {
                throw new NoChangeException("Error, insufficient coins for exact change.");
            }
        }
    }

    public void deltaExternal(String input) {
        switch (input) {
            case "q" -> {
                value += 25;
                quarters++;
            }
            case "d" -> {
                value += 10;
                dimes++;
            }
            case "n" -> {
                value += 5;
                nickels++;
            }
            default -> System.out.println("Error, invalid input.");
        }
    }

    public void deltaConfluent(String input) {
        try {
            this.lambda();
            this.deltaInternal();
            this.deltaExternal(input);
        } catch (NoChangeException exception) {
            System.out.println(exception.getMessage());
        }
    }
}