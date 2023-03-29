package com.company;

public class VendingMachine {
    private int nickels, dimes, quarters, value;
    private boolean change;

    public void changeLambda() throws NoChangeException {
        if (change) {
            int tempV = value;
            int tempQ = quarters;
            int tempD = dimes;
            int tempN = nickels;

            while(tempV > 0) {
                if (tempV >= 25 && tempQ >= 1) {
                    tempQ--;
                    tempV -= 25;
                    System.out.print("quarter ");
                } else if (tempV >= 10 && tempD >= 1) {
                    tempD--;
                    tempV -= 10;
                    System.out.print("dime ");
                } else if (tempV >= 5 && tempN >= 1) {
                    tempN--;
                    tempV -= 5;
                    System.out.print("nickel ");
                } else {
                    throw new NoChangeException("no sufficient coins for an exact change.");
                }
            }
            System.out.println();
        }
    }

    public void changeDelta() throws NoChangeException {
        if (change) {
            while(value > 0) {
                if (value >= 25 && quarters >= 1) {
                    quarters--;
                    value -= 25;
                } else if (value >= 10 && dimes >= 1) {
                    dimes--;
                    value -= 10;
                } else if (value >= 5 && nickels >= 1) {
                    nickels--;
                    value -= 5;
                } else {
                    throw new NoChangeException("no sufficient coins for an exact change.");
                }
            }
            change = false;
        }
    }

    public void dispenseLambda(){
        int temp = value;
        while (temp >= 100){
            temp -= 100;
            System.out.print("coffee ");
        }
        System.out.println();
    }

    public void dispenseDelta(){
        while (value >= 100){
            value -= 100;
        }
    }

    public void insertCoin(String coin){
        switch (coin) {
            case "nickel" -> {
                nickels += 1;
                value += 5;
            }
            case "dime" -> {
                dimes += 1;
                value += 10;
            }
            case "quarter" -> {
                quarters += 1;
                value += 25;
            }
        }
    }

    public void setChange(){ change = true; }

    public void printState() {
        System.out.println("Quarters: " + quarters + ", Dimes: " + dimes + ", Nickels: " + nickels
            + ", Value: " + value + ", Change: " + change);
    }

    public VendingMachine(int quarters, int dimes, int nickels, int value, boolean change){
        this.quarters = quarters;
        this.dimes = dimes;
        this.nickels = nickels;
        this.value = value;
        this.change = change;
    }
}
