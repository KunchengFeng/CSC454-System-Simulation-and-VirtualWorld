#include <iostream>
#include <fstream>
#include <string>
#include "VendingMachine.h"
#include "Event.h"
#include "EventQueue.h"

using namespace std;

int main()
{
    ifstream inputFile("Inputs[0].txt");
    if (!inputFile.is_open()) {
        cout << "Error, cannot open file.\n";
    }
    else {
        VendingMachine * machine = new VendingMachine(0, 0, 0, 0);
        EventQueue* events = new EventQueue();

        string line;
        string task;
        double time;
        int comma;

        while (getline(inputFile, line)) {
            comma = line.find(",");
            time = stod(line.substr(0, comma));
            task = line.substr(comma + 2);
            Event* event = new Event(time, task);
            events->enqueue(event);
        }
        inputFile.close();

        Event* scheduled = new Event(0.00, "nothing");
        Event* current;
        while (events->hasNext()) {                     // Time advance
            current = events->dequeue();
            if (scheduled->task == "nothing") {
                machine->deltaExternal(current->task);
                scheduled->time = current->time + 2.00;
                scheduled->task = "change";
            }
            else {
                if ((current->time - scheduled->time) < -0.01) {
                    machine->deltaExternal(current->task);
                    scheduled->time = current->time + 2.00;
                    scheduled->task = "change";
                }
                else if ((current->time - scheduled->time) > 0.01) {
                    try {
                        // Scheduled Event
                        cout << scheduled->time << "s: ";
                        machine->lambda();
                        machine->deltaInternal();
                        // Current Event
                        machine->deltaExternal(current->task);
                        scheduled->time = current->time + 2.00;
                        scheduled->task = "change";
                    }
                    catch (string message) {
                        cout << message;
                        exit(1);
                    }
                }
                else {
                    cout << current->time << "s: ";
                    machine->deltaConfluent(current->task);
                    scheduled->time = current->time + 2.00;
                    scheduled->task = "change";
                }
            }
        }

        if (scheduled->task == "change") {          // Last scheduled event
            try {
                cout << scheduled->time << "s: ";
                machine->lambda();
                machine->deltaInternal();
            }
            catch (string message) {
                cout << message << endl;
                exit(1);
            }
        }
    }

    cout << "Goodbye\n";
}