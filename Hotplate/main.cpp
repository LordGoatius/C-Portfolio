#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int ARRAY_SIZE = 10;

// Function Declarations //
void ConstructArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]);
void DisplayArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]);
void UpdateArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]);
bool ArrayDifference(const double hotPlate[ARRAY_SIZE][ARRAY_SIZE], const double previousHotPlate[ARRAY_SIZE][ARRAY_SIZE]);
void WriteToFile(const double hotPlate[ARRAY_SIZE][ARRAY_SIZE]);
void InputFile(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]);

int main() {
    double hotPlate[ARRAY_SIZE][ARRAY_SIZE];

    ConstructArray(hotPlate);
    double previousHotPlate[ARRAY_SIZE][ARRAY_SIZE];
    ConstructArray(previousHotPlate);

    cout << fixed << setprecision(3) << "Hotplate simulator" << endl;
    cout << endl;
    cout << "Printing the initial plate values..." << endl;
    DisplayArray(hotPlate);
    UpdateArray(hotPlate);
    cout << endl << "Printing plate after one iteration..." << endl;
    DisplayArray(hotPlate);

    while (ArrayDifference(hotPlate, previousHotPlate)) {
        UpdateArray(hotPlate);
        UpdateArray(previousHotPlate);
    }

    cout << endl << "Printing final plate..." << endl;
    DisplayArray(hotPlate);

    cout << endl << "Writing final plate to \"Hotplate.csv\"..." << endl;
    WriteToFile(hotPlate);

    cout << endl << "Printing input plate after 3 updates..." << endl;
    double hotPlateInput[ARRAY_SIZE][ARRAY_SIZE];
    InputFile(hotPlateInput);

    for (int i = 0; i < 3; i++) {
        UpdateArray(hotPlateInput);
    }

    DisplayArray(hotPlateInput);

    return 0;
}

// Part 1 - Initialize and Print 2D Array //
void ConstructArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            hotPlate[i][j] = 0.0;
        }
    }
    for (int i = 1; i < ARRAY_SIZE - 1; i++) {
        hotPlate[0][i] = 100.0;
        hotPlate[ARRAY_SIZE - 1][i] = 100.0;
    }
}

void DisplayArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE - 1; j++) {
            cout << setw(9) << hotPlate[i][j] << ",";
        }
        cout << setw(9) << hotPlate[i][ARRAY_SIZE - 1] << endl;
    }
}

// Part 2 - Update Elements Once //
void UpdateArray(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    double updatedHotPlate[ARRAY_SIZE][ARRAY_SIZE];

    ConstructArray(updatedHotPlate);
    for (int i = 1; i < ARRAY_SIZE - 1; i++) {
        for (int j = 1; j < ARRAY_SIZE - 1; j++) {
            updatedHotPlate[i][j] = (hotPlate[i + 1][j] + hotPlate[i - 1][j] + hotPlate[i][j + 1] + hotPlate[i][j - 1]) / 4;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            hotPlate[i][j] = updatedHotPlate[i][j];
        }
    }
}

// Part 3 - Repeat Update until Steady State is Achieved //
bool ArrayDifference(const double hotPlate[ARRAY_SIZE][ARRAY_SIZE], const double previousHotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    double maxDifference = 0.0;
    for (int i = 1; i < ARRAY_SIZE - 1; i++) {
        for (int j = 1; j < ARRAY_SIZE - 1; j++) {
            if ((hotPlate[i][j] - previousHotPlate[i][j]) > maxDifference) {
                maxDifference = hotPlate[i][j] - previousHotPlate[i][j];
            }
        }
    }
    if (maxDifference > 0.1) {
        return true;
    }
    else {
        return false;
    }
}

// Part 4 - Write Data to a File //
void WriteToFile(const double hotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    ofstream hotPlateFS;
    hotPlateFS.open("Hotplate.csv");

    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE - 1; j++) {
            hotPlateFS << fixed << setprecision(3) << hotPlate[i][j] << ",";
        }
        hotPlateFS << hotPlate[i][ARRAY_SIZE - 1] << endl;
    }
    hotPlateFS << endl;
    hotPlateFS.close();
}

// Part 5 - Input Plate //
void InputFile(double hotPlate[ARRAY_SIZE][ARRAY_SIZE]) {
    ifstream hotPlateFS;
    hotPlateFS.open("Inputplate.txt");

    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            hotPlateFS >> hotPlate[i][j];
        }
    }
    hotPlateFS.close();
}