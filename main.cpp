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
const int WIDTH = 10;
const int DECIMAL_PRECISION = 3;
string filename = "Inputplate.txt";

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

void Print(double hot_plate[][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << fixed << setprecision(DECIMAL_PRECISION) << setw(WIDTH) << hot_plate[row][col];
            if (col < SIZE - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void FirstAverage(double hot_plate[][SIZE], double copy_hot_plate[][SIZE]) {
    double average_temp;

    for (int i = 1; i < SIZE - 1; i++) {
        for (int col = 1; col < SIZE - 1; col++) {
            average_temp = (hot_plate[i - 1 ][col] + hot_plate[i + 1][col] + hot_plate[i][col - 1] + hot_plate[i][col + 1]) / NEIGHBORS;
            copy_hot_plate[i][col] = average_temp;
        }
    }
}

void MyAverage(double hot_plate[][SIZE], double copy_hot_plate[][SIZE]) {

    bool keepGoing;
    const double CHANGE = 0.1;
    const double neighbors = 4.0;

    do {
        keepGoing = false;
        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {

                copy_hot_plate[row][column] = (hot_plate[row + 1][column] + hot_plate[row - 1][column] + hot_plate[row][column + 1] + hot_plate[row][column - 1]) / neighbors;
                if (abs(hot_plate[row][column] - copy_hot_plate[row][column]) > CHANGE) {
                    keepGoing = true;
                }
            }
        }

        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {
                hot_plate[row][column] = copy_hot_plate[row][column];
            }
        }
    } while (keepGoing);
}

void SaveFile(double hot_plate[][SIZE]) {
    ofstream out;
    out.open("Hotplate.csv");

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            out << fixed << fixed << setprecision(DECIMAL_PRECISION) << setw(WIDTH) << hot_plate[row][col];
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
    double hot_plate[SIZE][SIZE];
    double copy_hot_plate[SIZE][SIZE];
    bool keepGoing;
    const double CHANGE = 0.1;
    const double neighbors = 4.0;

    cout << "Hotplate simulator" << endl << endl;
    cout << "Printing the initial plate values..." << endl;
    Initial(hot_plate);
    Initial(copy_hot_plate);
    Print(hot_plate);

    cout << endl << endl;

    cout << "Printing plate after one iteration..." << endl;
    FirstAverage(hot_plate, copy_hot_plate);
    Print(copy_hot_plate);

    cout << endl << endl;

    cout << "Printing final plate..." << endl;
    MyAverage(hot_plate, copy_hot_plate);
    Print(hot_plate);

    cout << endl << "Writing final plate to \"Hotplate.csv\"" << endl;
    SaveFile(hot_plate);


    ifstream in;
    in.open(filename);

    cout << endl << "Printing input plate after 3 updates..." << endl;
    for (int k = 1; k < 3; k++) {
        for (int row = 1; row < SIZE - 1; row++) {
            for (int column = 1; column < SIZE - 1; column++) {

                copy_hot_plate[row][column] = (hot_plate[row + 1][column] + hot_plate[row - 1][column] + hot_plate[row][column + 1] + hot_plate[row][column - 1]) / neighbors;
                if (abs(hot_plate[row][column] - copy_hot_plate[row][column]) > CHANGE) {
                }
            }
            for (row= 1; row < SIZE - 1; row++) {
                for (int column = 1; column < SIZE - 1; column++) {
                    hot_plate[row][column] = copy_hot_plate[row][column];
                }
            }
            Print(copy_hot_plate);
        }
    }
    system("pause");
    return 0;
}