#include <iostream>
#include "NetworkModel.h"

int main()
{
    string input;
    int a, b = 0;
    bool ready = false;
    NetworkModel* model = new NetworkModel(0, 0, 0, 0);

    cout << "Welcome to the network model." << endl;
    while (true) {
        cin >> input;
        if (input == "exit") {
            break;
        }
        else {

            for (int i = 0; i < input.length(); i++) {
                if (input.at(i) == '1' || input.at(i) == '0') {
                    if (!ready) {
                        a = input.at(i);
                        ready = true;
                    }
                    else {
                        b = input.at(i);
                        ready = false;

                        for (int j = 0; j < 3; j++) {
                            model->lambda();
                            model->coupling(a, b);
                            model->delta();
                            model->printState();
                        }
                    }
                }
            }
        }
    }

    cout << "Goodbye." << endl;
    model->delteComponents();
    delete model;
};