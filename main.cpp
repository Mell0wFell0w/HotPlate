#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int SIZE = 10;
const double NEIGHBORS = 4.0;
const int LEFT = 0;
const int RIGHT = 9;
const int WIDTH = 9;
const int DECIMAL_PRECISION = 3;


void Initial(double hotPlate[][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (row == LEFT || row == RIGHT) {
                if (col == LEFT || col == RIGHT) {
                    hotPlate[row][col] = 0;
                }
                else {
                    hotPlate[row][col] = 100;
                }
            }
            else {
                hotPlate[row][col] = 0;
            }
        }
    }
}

void Print(double hotPlate[][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << fixed << setprecision(DECIMAL_PRECISION) << setw(WIDTH) << hotPlate[row][col];
            if (col < SIZE - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void FirstAverage(double hotPlate[][SIZE], double copyHotPlate[][SIZE]) {
    double average_temp;

    for (int i = 1; i < SIZE - 1; i++) {
        for (int col = 1; col < SIZE - 1; col++) {
            average_temp = (hotPlate[i - 1 ][col] + hotPlate[i + 1][col] + hotPlate[i][col - 1] + hotPlate[i][col + 1]) / NEIGHBORS;
            copyHotPlate[i][col] = average_temp;
        }
    }
}

void MyAverage(double hotPlate[][SIZE], double copyHotPlate[][SIZE]) {

    bool keepGoing;
    const double CHANGE = 0.1;
    const double neighbors = 4.0;

    do {
        keepGoing = false;
        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {

                copyHotPlate[row][column] = (hotPlate[row + 1][column] + hotPlate[row - 1][column] + hotPlate[row][column + 1] + hotPlate[row][column - 1]) / neighbors;
                if (abs(hotPlate[row][column] - copyHotPlate[row][column]) > CHANGE) {
                    keepGoing = true;
                }
            }
        }

        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {
                hotPlate[row][column] = copyHotPlate[row][column];
            }
        }
    } while (keepGoing);
}

void SaveFile(double hotPlate[][SIZE]) {
    ofstream out;
    out.open("Hotplate.csv");

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            out << fixed << fixed << setprecision(DECIMAL_PRECISION) << setw(WIDTH) << hotPlate[row][col];
            if (col < SIZE - 1) {
                out << ",";
            }
        }
        out << endl;
    }
    out.close();
}

//void ReadFile(double hot_plate[][SIZE])
//{
//
//}

int main() {
    double hotPlate[SIZE][SIZE];
    double copyHotPlate[SIZE][SIZE];
    //bool keepGoing;
    const double CHANGE = 0.1;
    const double neighbors = 4.0;
    string filename = "Inputplate.txt";

    cout << "Hotplate simulator" << endl << endl;
    cout << "Printing the initial plate values..." << endl;
    Initial(hotPlate);
    Initial(copyHotPlate);
    Print(hotPlate);

    cout << endl << endl;

    cout << "Printing plate after one iteration..." << endl;
    FirstAverage(hotPlate, copyHotPlate);
    Print(copyHotPlate);

    cout << endl << endl;

    cout << "Printing final plate..." << endl;
    MyAverage(hotPlate, copyHotPlate);
    Print(hotPlate);

    cout << endl << "Writing final plate to \"Hotplate.csv\"" << endl;
    SaveFile(hotPlate);


    ifstream in;
    in.open(filename);

    cout << endl << "Printing input plate after 3 updates..." << endl;
    for (int k = 1; k < 3; k++) {
        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {

                copyHotPlate[row][column] = (hotPlate[row + 1][column] + hotPlate[row - 1][column] + hotPlate[row][column + 1] + hotPlate[row][column - 1]) / neighbors;
                if (abs(hotPlate[row][column] - copyHotPlate[row][column]) > CHANGE) {
                }
            }
            for (row= 1; row < SIZE - 1; row++) {
                for (int column = 1; column < SIZE - 1; column++) {
                    hotPlate[row][column] = copyHotPlate[row][column];
                }
            }
            Print(copyHotPlate);
        }
    }
    system("pause");
    return 0;
}
