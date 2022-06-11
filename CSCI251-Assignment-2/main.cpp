#include <iostream>
#include "shapeTwoD.h"
#include "cross.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "points.h"

using namespace std;

void displayMenu();
void inputSensorData(string& shapeName, bool& warp);
void computeAreaAllRecords();
void printShapesReport();
void sortShapeData();
void setCircle(const string& shapeName, const bool& warp);
void setNonCircular(const string& shapeName, const bool& warp);
void mallocFree();
void print();
bool sortASC(ShapeTwoD* i, ShapeTwoD* k);
bool sortDESC(ShapeTwoD* i, ShapeTwoD* k);
bool sortTA(ShapeTwoD* i, ShapeTwoD* k);

vector<ShapeTwoD*> shapeList;

int main() {
    string shapeName = "";
    bool warp = false;
    int choice = 0;
 
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            inputSensorData(shapeName, warp);
            break;

        case 2:
            computeAreaAllRecords();
            break;

        case 3:
            printShapesReport();
            break;

        case 4:
            sortShapeData();
            break;
        }
    } while (choice != 0);
    cout << "Program terminated!" << endl;
    mallocFree();
    return 0;
}

void displayMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to Assn2 program!" << endl << endl;
    cout << "1)" << setw(4) << " " << "Input sensor data" << endl;
    cout << "2)" << setw(4) << " " << "Compute area (for all records)" << endl;
    cout << "3)" << setw(4) << " " << "Print shapes report" << endl;
    cout << "4)" << setw(4) << " " << "Sort shape data" << endl;
    cout << "0)" << setw(4) << " " << "Quit program" << endl << endl;
    cout << "Please enter your choice: ";
}

void inputSensorData(string& shapeName, bool& warp) {
    string warpability;
    cout << "\n[ Input sensor data ]" << endl;

    cout << "Please enter name of shape: ";
    cin >> shapeName;

    cout << "Please enter special type: ";
    cin >> warpability;
    cout << endl;

    equalsIgnoreCase(warpability, "NS") ? warp = false : 
    equalsIgnoreCase(warpability, "WS") ? warp = true  : warp = false;

    if (equalsIgnoreCase(shapeName, "Circle")) {
        setCircle(shapeName, warp);
    }
    else if (equalsIgnoreCase(shapeName, "Cross") || 
             equalsIgnoreCase(shapeName, "Rectangle") || 
             equalsIgnoreCase(shapeName, "Square")) {
        setNonCircular(shapeName, warp);
    } else {
        cout << "[-] ERROR: INVALID SHAPE NAME!\nEXITING TO MAIN MENU!" << endl;
        return;
    }
    cout << "\nRecord successfully stored. Going back to main menu ...\n" << endl;
}

void computeAreaAllRecords() {
    if (shapeList.size() == 0) {
        cout << "No records found!" << endl;
    }
    else {
        for (size_t i = 0; i < shapeList.size(); i++) {
            double area = shapeList[i]->computeArea();
            shapeList[i]->setArea(area);
        }
        cout << endl << "Computation completed! ( " << shapeList.size() << " records were updated )" << endl << endl;
    }
}


void printShapesReport() {
    cout << "\nTotal no. of records available = " << shapeList.size() << endl << endl;
    print();
    cout << endl << endl;
}


void sortShapeData() {
    char option = ' ';

    cout << endl;
    cout << "a)" << setw(4) << " " << "Sort by area (ascending)" << endl;
    cout << "b)" << setw(4) << " " << "Sort by area (descending)" << endl;
    cout << "c)" << setw(4) << " " << "Sort by special type and area" << endl << endl;
    cout << "Please select sort option('q' to go main menu): ";
    cin >> option;

    switch (option) {
        case 'a':
            cout << endl << "Sort by area (largest to smallests) ..." << endl;
            sort(shapeList.begin(), shapeList.end(), sortASC);
            break;
       case 'b':
            cout << endl << "Sort by area (smallests to largest) ..." << endl;
            sort(shapeList.begin(), shapeList.end(), sortDESC);
            break;

        case 'c':
            cout << endl << "Sort by special type and area (largest to smallests) ..." << endl;
            sort(shapeList.begin(), shapeList.end(), sortTA);
            break;

        case 'q':
        default:
            return;
            break;
    }
    print();
}


void setNonCircular(const string& shapeName, const bool& warp) {
    size_t index = shapeList.size();
    vector<Points> temp;
    int size = equalsIgnoreCase(shapeName, "Cross") ? 12 : 4;
    cout << "There are total of " << size << " co - ordinates..." << endl;
    for (int i = 0; i < size; i++) {
        Points p;
        cout << "[" << i + 1 << "] Please enter x-coordindate: ";
        cin >> p.x;
        cout << "[" << i + 1 << "] Please enter y - coordindate: ";
        cin >> p.y;
        temp.push_back(p);
    }

    (equalsIgnoreCase(shapeName, "Square")     ? shapeList.push_back(new Square(shapeName, warp, temp, index))    :
    (equalsIgnoreCase(shapeName, "Rectangle")) ? shapeList.push_back(new Rectangle(shapeName, warp, temp, index)) :
                                                 shapeList.push_back(new Cross(shapeName, warp, temp, index)));
}

void setCircle(const string& shapeName, const bool& warp) {
    size_t index = shapeList.size();
    int x, y, radius;
    cout << "Please enter x-coordinate of center: ";
    cin >> x;
    cout << "Please enter y-coordinate of center: ";
    cin >> y;
    cout << "Please enter radius (units): ";
    cin >> radius;
    shapeList.push_back(new Circle(shapeName, warp, x, y, radius, index));
}


void mallocFree() {
    for (size_t i = 0; i < shapeList.size(); i++)
        delete shapeList[i];
}

void print() {
    for (size_t i = 0; i < shapeList.size(); i++) {
        cout << shapeList[i]->toString() << endl;
    }
}


bool sortASC(ShapeTwoD* curr, ShapeTwoD* prev) {
    return curr->getArea() < prev->getArea();
}

bool sortDESC(ShapeTwoD* curr, ShapeTwoD* prev) {
    return curr->getArea() > prev->getArea();
}

bool sortTA(ShapeTwoD* curr, ShapeTwoD* prev) {
    if (curr->getContainsWarpSpace() != prev->getContainsWarpSpace()) {
        return curr->getContainsWarpSpace() > prev->getContainsWarpSpace();
    }

    if (curr->computeArea() != prev->computeArea()) {
        return curr->getArea() > prev->getArea();
    }

    return false;
}
