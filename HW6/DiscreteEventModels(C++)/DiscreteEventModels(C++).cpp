// main function is here
#include <iostream>
#include <fstream>
#include <string>
#include <Event.h>
#include <PressDrillModel.h>
#include <Moment.h>
#include <MinHeap.h>

using namespace std;

int main()
{
    cout << "Testing AtomicModel" << endl;

    PressDrillModel* press = new PressDrillModel(1);
    PressDrillModel* drill = new PressDrillModel(2);

    cout << "AtomicModel is fine\n" << endl;
    cout << "Testing MinHeap..." << endl;

    MinHeap* events = new MinHeap();

    // Read a file and create input events
    ifstream inputFile("HW6(C++)_Inputs.txt");
    if (!inputFile.is_open()) {
        cout << "Error, cannot open file.\n";
    }
    else {
        string line;
        string input = "input";
        int value;
        double real;
        int discrete;
        int comma;
        int space;

        while (getline(inputFile, line)) {
            comma = line.find(",");
            space = line.find(" ");
            real = stod(line.substr(0, comma));
            discrete = stoi(line.substr(comma + 1, space));
            value = stoi(line.substr(space + 1));
            Moment* moment = new Moment(real, discrete);
            Event* event = new Event(moment, press, input, value);
            events->insert(event);
        }
        inputFile.close();
    }

    events->peak();
    cout << "MinHeap and Events inserted\n" << endl;

    return 0;
}

