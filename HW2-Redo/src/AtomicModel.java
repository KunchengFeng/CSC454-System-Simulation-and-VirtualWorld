public class AtomicModel {
    //lambda: S -> Y
    //delta: (X, S) -> S
    State state;

    public AtomicModel(int nickels, int dimes, int quarters, int value, boolean change) {
        state = new State(nickels, dimes, quarters, value, change);
    }

    public String lambda() throws NoChangeException {
        StringBuilder output = new StringBuilder();
        int value = state.value;

        if (state.change) {
            int quarters = state.quarters;
            int dimes = state.dimes;
            int nickel = state.nickels;

            while (value > 0) {
                if (value >= 25 && quarters > 0) {
                    value -= 25;
                    quarters--;
                    output.append("quarter ");
                } else if (value >= 10 && dimes > 0) {
                    value -= 10;
                    dimes--;
                    output.append("dime ");
                } else if (value >= 5 && nickel > 0) {
                    value -= 5;
                    nickel--;
                    output.append("nickel ");
                } else {
                    throw new NoChangeException("Error, no sufficient coins for an exact change.");
                }
            }
        } else {

            while (value >= 100) {
                value -= 100;
                output.append("coffee ");
            }
        }

        return output.toString();
    }

    public void delta(String input) throws NoChangeException {
        char c;

        if (state.change) {

            while (state.value > 0) {
                if (state.value >= 25 && state.quarters > 0) {
                    state.value -= 25;
                    state.quarters--;
                } else if (state.value >= 10 && state.dimes > 0) {
                    state.value -= 10;
                    state.dimes--;
                } else if (state.value >= 5 && state.nickels > 0) {
                    state.value -= 5;
                    state.nickels--;
                } else {
                    throw new NoChangeException("Error, no sufficient coins for an exact change.");
                }
            }
            state.change = false;
        } else { while (state.value >= 100) { state.value -= 100; } }

        for (int i = 0; i < input.length(); i++) {
            c = input.charAt(i);

            if (c == 'q') {
                state.quarters++;
                state.value += 25;
            } else if (c == 'd') {
                state.dimes++;
                state.value += 10;
            } else if (c == 'n') {
                state.nickels++;
                state.value += 5;
            } else if (c == 'c') {
                state.change = true;
            } else if (c == 'w') {
                try {
                    System.out.println(this.lambda());
                    if (i == input.length()-1) {
                        this.delta("");
                    } else {
                        this.delta(input.substring(i+1));
                        break;
                    }
                } catch (NoChangeException exception) {
                    System.out.println(exception.getMessage());
                    System.exit(1);
                }
            } else {
                System.out.println("Error, unknown input.");
            }
        }
    }

    public void printState() {
        System.out.println("{ quarters: " + state.quarters + ", dimes: " + state.dimes + ", nickels: " + state.nickels
                            + ", value: " + state.value + ", change: " + state.change + " }");
    }
}

class State {
    int quarters, dimes, nickels, value;
    boolean change;

    State(int nickels, int dimes, int quarters, int value, boolean change) {
        this.quarters = quarters;
        this.dimes = dimes;
        this.nickels = nickels;
        this.value = value;
        this.change = change;
    }
}