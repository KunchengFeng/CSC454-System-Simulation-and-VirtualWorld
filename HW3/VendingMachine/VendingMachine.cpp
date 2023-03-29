#include <iostream>
#include <string>
#include "AtomicModel.h"
using namespace std;

int main()
{
    AtomicModel * model = new AtomicModel(0, 0, 0, 0, false);
    string input;
    cout << "Welcome to the vending machine." << endl;

    while (true) {
        getline(cin, input);

        if (input == "exit") {
            break;
        }
        else {
            try {
                model->lambda();
                model->delta(input);
                model->printState();
            }
            catch (string message) {
                cout << message << endl;
                exit(1);
            }
        }
    }

    cout << "Have a nice day!" << endl;
    delete model;
    return 0;
}
