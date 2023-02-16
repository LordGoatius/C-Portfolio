#include <fstream>
#include <sstream>
#include <iostream>

#include "Deque.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Station.hpp"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

struct Car {
    unsigned id_;
    Car() : id_(0) {}
    Car(const unsigned int& id) : id_(id) {}
    ~Car() {}

    bool operator==(const Car& car) const {
        if (id_ == car.id_) {
            return true;
        }
        return false;
    }

    bool operator!=(const Car& car) const {
        return !this->operator==(car);
    }

    friend ostream& operator<<(ostream& os, const Car& d) {
        os << d.toString();
        return os;
    }

    string toString() const {
        ostringstream oss;
        oss << id_;
        return oss.str();
    }
};

int main(int argc, char* argv[]) {
    VS_MEM_CHECK
        //intalize command line args
        if (argc < 3) {
            cerr << "Please provide name of input and output files";
            return 1;
        }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    Station<Car> station;

    bool continueMenuLoop = true;
    int count = 0;
    while (continueMenuLoop) {
        string line;
        getline(in, line);
        istringstream iss(line);
        string userMenuChoice;
        iss >> userMenuChoice;

        if (userMenuChoice == "Add:station") {
            int data;
            iss >> data;
            string output = station.addCar(Car(data));
            out << line << " " << output << endl;
        }
        else if (userMenuChoice == "Add:queue") {
            out << line << " " << station.addQueue() << endl;
        }
        else if (userMenuChoice == "Add:stack") {
            out << line << " " << station.addStack() << endl;
        }
        else if (userMenuChoice == "Remove:station") {
            out << line << " " << station.removeCar() << endl;
        }
        else if (userMenuChoice == "Remove:queue") {
            out << line << " " << station.removeQueue() << endl;
        }
        else if (userMenuChoice == "Remove:stack") {
            out << line << " " << station.removeStack() << endl;
        }
        else if (userMenuChoice == "Top:station") {
            out << line << " " << station.topCar() << endl;
        }
        else if (userMenuChoice == "Top:queue") {
            out << line << " " << station.topQueue() << endl;
        }
        else if (userMenuChoice == "Top:stack") {
            out << line << " " << station.topStack() << endl;
        }
        else if (userMenuChoice == "Size:train") {
            out << line << " " << station.sizeTrain() << endl;
        }
        else if (userMenuChoice == "Size:queue") {
            out << line << " " << station.sizeQueue() << endl;
        }
        else if (userMenuChoice == "Size:stack") {
            out << line << " " << station.sizeStack() << endl;
        }
        else if (userMenuChoice == "Queue") {
            out << line << " " << station.outQueue() << endl;
        }
        else if (userMenuChoice == "Stack") {
            out << line << " " << station.outStack() << endl;
        }
        else if (userMenuChoice == "Train") {
            out << line << " " << station.outTrain() << endl;
        }
        else if (userMenuChoice == "Find") {
            int data;
            iss >> data;
            Car car(data);
            out << line << " " << station.find(car) << endl;
        }
        else if (line == "" || line == "\n") {
            continueMenuLoop = true;
            ++count;
            if (count > 400) break;
            continue;
        }
        else {
            continueMenuLoop = false;
        }
    }
}