#include <iostream>
#include <stdio.h>
#include <fstream>
#include <set>
#include <string>   
#include <regex>
#include "MyTemplates.h"
#include "Line2D.h"
#include "Line3D.h"
#include "Point2D.h"
#include "Point3D.h"

using namespace std;

ostream& fmtSM(ostream& os, const int& size, const string& option, const string& line);
void switcher(const string& fileCrit, string& sortCrit, bool& sorted);
void displayMenu(const string& fileCrit, string& sortCrit, const string& sortOrd, bool& sorted);
void config(string& fileName, bool& configured);
void specfileCrit(string& fileCrit, bool& sorted);
void specSortCrit(string& sortCrit, const string& fileCrit, bool& sorted);
void specSortOrd(string& sortOrd);
void view(const string& fileCrit, const string& sortCrit, const string& sortOrd, const bool& configured);
void store(const string& fileCrit, const string& sortCrit, const string& sortOrd, const bool& configured);
void prompter(const int& choice);

set<string> information;
vector<Line2D> line2DList;
vector<Line3D> line3DList;
vector<Point2D> point2DList;
vector<Point3D> point3DList;

int main() {
    string fileCrit = "Point2D", sortCrit = "x-ordinate", sortOrd = "ASC", fileName;
    bool sorted = false, configured = false;
    int choice;

    do {
        displayMenu(fileCrit, sortCrit, sortOrd, sorted);
        cin >> choice;

        switch (choice) {
            case 1:
                config(fileName, configured);
                break;
            case 2:
                specfileCrit(fileCrit, sorted);
                break;
            case 3:
                specSortCrit(sortCrit, fileCrit, sorted);
                break;
            case 4:
                specSortOrd(sortOrd);
                break;
            case 5:
                view(fileCrit, sortCrit, sortOrd, configured);
                break;
            case 6:
                store(fileCrit, sortCrit, sortOrd, configured);
                break;
            case 0:
            default:
				break;
        }
        prompter(choice);
    } while (choice != 0);
    cout << "Program terminated!" << endl;
    return 0;
}

ostream& fmtSM(ostream& cout, const int& size, const string& option, const string& line = "") {
    line == "" ? cout << right << setw(size) << " " << option : cout << right << setw(size) << " " << option << right << setw(size) << " " << line << endl;
    return cout.flush();
}

void displayMenu(const string& fileCrit, string& sortCrit, const string& sortOrd, bool& sorted) {
    switcher(fileCrit, sortCrit, sorted);
    cout << "Student ID" << setw(5) << ": " << 7058810 << endl;
    cout << "Student Name : Min Zhan Foo" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to Assn3 program!" << endl << endl;
    cout << "1)" << setw(4) << " " << "Read in data" << endl;
    cout << "2)" << setw(4) << " " << "Specify filerting criteria (current: " << fileCrit << ")" << endl;
    cout << "3)" << setw(4) << " " << "Specify sorting criteria (current: " << sortCrit << ")" << endl;
    cout << "4)" << setw(4) << " " << "Specify sorting order (current: " << sortOrd << ")" << endl;
    cout << "5)" << setw(4) << " " << "View data" << endl;
    cout << "6)" << setw(4) << " " << "Store data" << endl;
    cout << "0)" << setw(4) << " " << "Quit program" << endl << endl;
    cout << "Please enter your choice: ";
}

void config(string& fileName, bool& configured) {
    cout << endl << "Please enter filename: ";
    cin >> fileName;

    if (fileName.find(".txt") == string::npos)
        fileName += ".txt";

    if (fileExists(fileName)) {
        if (!line2DList.empty()) {
            line2DList.clear();
        }
        if (!line3DList.empty()) {
            line3DList.clear();
        }
        if (!point2DList.empty()) {
            point2DList.clear();
        }
        if (!point3DList.empty()) {
            point3DList.clear();
        }
        ifstream read(fileName);
        string line;

        while (!read.eof()) {
            getline(read, line);
            if (line != "\n" && line != " " && line != "\0" && line != "" && line != "\r" && line != "\r\n") {
                information.emplace(line);
            }
        }
        cout << endl << information.size() << " records read in successfully!" << endl << endl;
        string reg = "[, \\[\\]]";

        set<string>::iterator value = information.begin();

        while (value != information.end()) {
            vector<string> tokens = tokenizer(*value, reg);

            if (equalsIgnoreCase(tokens[0], "Line2D")) {
                line2DList.push_back(Line2D(Point2D(stoi(tokens[1]), stoi(tokens[2])), Point2D(stoi(tokens[3]), stoi(tokens[4]))));
            }
            else if (equalsIgnoreCase(tokens[0], "Line3D")) {
                line3DList.push_back(Line3D(Point3D(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3])), Point3D(stoi(tokens[4]), stoi(tokens[5]), stoi(tokens[6]))));
            }
            else if (equalsIgnoreCase(tokens[0], "Point2D")) {
                point2DList.push_back(Point2D(stoi(tokens[1]), stoi(tokens[2])));
            }
            else if (equalsIgnoreCase(tokens[0], "Point3D")) {
                point3DList.push_back(Point3D(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3])));
            }
            tokens.clear();
            value++;
        }
        configured = true;
    }
    else {
        cout << fileName << " does not exist! Heading back to main menu..." << endl << endl;
        return;
    }
}

void specfileCrit(string& fileCrit, bool& sorted) {
    if (sorted) sorted = false;
    char option = 'x';

    cout << "[ Specifying filtering criteria (current: " << fileCrit << ") ]" << endl << endl;
    fmtSM(cout, 5, "a)", "Point2D records");
    fmtSM(cout, 5, "b)", "Point3D records");
    fmtSM(cout, 5, "c)", "Line2D records");
    fmtSM(cout, 5, "d)", "Line3D records");
    cout << endl;
    fmtSM(cout, 5, "Please enter your criteria (a - d): ", "");
    cin >> option;

    switch (option) {
    case 'a':
    case 'A':
        fileCrit = "Point2D";
        break;
    case 'b':
    case 'B':
        fileCrit = "Point3D";
        break;
    case 'c':
    case 'C':
        fileCrit = "Line2D";
        break;
    case 'd':
    case 'D':
        fileCrit = "Line3D";
        break;
    default:
        cout << "Invalid option! Returning to main menu...";
        return;
        break;
    }
    cout << right << setw(5) << " " << "Filter criteria successfully set to '" << fileCrit << "'!" << endl;
}

void specSortCrit(string& sortCrit, const string& fileCrit, bool& sorted) {
    char option = 'x';
    int x = 0;
    cout << "[ Specifying sorting criteria (current: " << sortCrit << ") ]" << endl << endl;
    if (equalsIgnoreCase(fileCrit, "Point2D")) {
        x = 1;
        fmtSM(cout, 5, "a)", "x-ordinate values");
        fmtSM(cout, 5, "b)", "y-ordinate values");
        fmtSM(cout, 5, "c)", "Dist. Fr Origin value");
    }
    else if (equalsIgnoreCase(fileCrit, "Point3D")) {
        x = 2;
        fmtSM(cout, 5, "a)", "x-ordinate values");
        fmtSM(cout, 5, "b)", "y-ordinate values");
        fmtSM(cout, 5, "c)", "z-ordinate values");
        fmtSM(cout, 5, "d)", "Dist. Fr Origin value");
    }
    else if (equalsIgnoreCase(fileCrit, "Line2D") || equalsIgnoreCase(fileCrit, "Line3D")) {
        x = 3;
        fmtSM(cout, 5, "a)", "Pt 1's (x, y) values");
        fmtSM(cout, 5, "b)", "Pt 2's (x, y) values");
        fmtSM(cout, 5, "c)", "length value");
    }

    cout << endl;
    equalsIgnoreCase(fileCrit, "Point2D") || equalsIgnoreCase(fileCrit, "Line2D") || equalsIgnoreCase(fileCrit, "Line3D") ?
        fmtSM(cout, 5, "Please enter your criteria (a - c): ", "") : fmtSM(cout, 5, "Please enter your criteria (a - d): ", "");
    cin >> option;

    switch (x) {
    case 1:
        switch (option) {
        case 'a':
        case 'A':
            sortCrit = "x-ordinate";
            break;

        case 'b':
        case 'B':
            sortCrit = "y-ordinate";
            break;

        case 'c':
        case 'C':
            sortCrit = "Dist. Fr Origin";
            break;
        }
        break;

    case 2:
        switch (option) {
        case 'a':
        case 'A':
            sortCrit = "x-ordinate";
            break;

        case 'b':
        case 'B':
            sortCrit = "y-ordinate";
            break;

        case 'c':
        case 'C':
            sortCrit = "z-ordinate";
            break;

        case 'd':
        case 'D':
            sortCrit = "Dist. Fr Origin";
            break;
        }
        break;

    case 3:
        switch (option) {
        case 'a':
        case 'A':
            sortCrit = "Pt. 1";
            break;

        case 'b':
        case 'B':
            sortCrit = "Pt. 2";
            break;

        case 'c':
        case 'C':
            sortCrit = "Length";
            break;
        }
        break;
    }
    cout << right << setw(5) << " " << "Sorting criteria successfully set to '" << sortCrit << "'!" << endl;
    sorted = true;
}

void specSortOrd(string& sortOrd) {
    char option = 'x';

    cout << "[ Specifying sorting order(current: " << sortOrd << ") ]" << endl << endl;
    fmtSM(cout, 5, "a)", "ASC (Ascending order)");
    fmtSM(cout, 5, "b)", "DSC (Descending order)");
    cout << endl;
    fmtSM(cout, 5, "Please enter your criteria (a - b): ", "");
    cin >> option;

    switch (option) {
    case 'a':
    case 'A':
        sortOrd = "ASC";
        break;
    case 'b':
    case 'B':
        sortOrd = "DSC";
        break;
    default:
        cout << "Invalid option! Returning to main menu...";
        return;
        break;
    }
    cout << right << setw(5) << " " << "Sorting order successfully set to '" << sortOrd << "'!" << endl;
}

void switcher(const string& fileCrit, string& sortCrit, bool& sorted) {
    if (!sorted) equalsIgnoreCase(fileCrit, "Point2D") || equalsIgnoreCase(fileCrit, "Point3D") ? sortCrit = "x-ordinate" : sortCrit = "Pt. 1";
}

void view(const string& fileCrit, const string& sortCrit, const string& sortOrd, const bool& configured) {
    if (configured) {
        cout << "\n[ View data ... ]" << endl;
        cout << "filtering criteria: " << fileCrit << endl;
        cout << "sorting criteria: " << sortCrit << endl;
        cout << "sorting order: " << sortOrd << endl << endl;

        if (equalsIgnoreCase(fileCrit, "Line2D")) {
            cout << right << setw(1) << " " << "P1-X" << right << setw(2) << " " << "P1-Y" <<
                right << setw(5) << " " << "P2-X" << right << setw(2) << " " << "P2-Y" <<
                right << setw(4) << " " << "Length" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - " << endl;

            if (equalsIgnoreCase(sortCrit, "Pt. 1")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), pt1Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line2DList.rbegin(), line2DList.rend(), pt1Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Pt. 2")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), pt2Order());
                }
                else {
                    sort(line2DList.rbegin(), line2DList.rend(), pt2Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Length")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), dist_lenScalarOrder());
                }
                else {
                    sort(line2DList.rbegin(), line2DList.rend(), dist_lenScalarOrder());
                }
            }
            for (size_t i = 0; i < line2DList.size(); i++) {
                cout << line2DList[i];
            }
            cout << endl << endl;
        }

        if (equalsIgnoreCase(fileCrit, "Line3D")) {
            cout << right << setw(1) << " " << "P1-X" << right << setw(2) << " " << "P1-Y" << right << setw(2) << " " << "P1-Z"
                << right << setw(5) << " " << "P2-X" << right << setw(2) << " " << "P2-Y" << right << setw(2) << " " << "P2-Z"
                << right << setw(4) << " " << "Length" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

            if (equalsIgnoreCase(sortCrit, "Pt. 1")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), pt1Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), pt1Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Pt. 2")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), pt2Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), pt2Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Length")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), dist_lenScalarOrder());
                }
            }
            for (size_t i = 0; i < line3DList.size(); i++) {
                cout << line3DList[i];
            }
            cout << endl << endl;
        }

        if (equalsIgnoreCase(fileCrit, "Point2D")) {
            cout << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(4) << " " << "Dist. Fr Origin" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

            if (equalsIgnoreCase(sortCrit, "x-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), xOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), xOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "y-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), yOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), yOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Dist. Fr Origin")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), dist_lenScalarOrder());
                }
            }

            for (size_t i = 0; i < point2DList.size(); i++) {
                cout << point2DList[i];
            }
            cout << endl << endl;
        }

        if (equalsIgnoreCase(fileCrit, "Point3D")) {
            cout << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(6) << "Z" << right << setw(4) << " " << "Dist. Fr Origin" << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

            if (equalsIgnoreCase(sortCrit, "x-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), xOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), xOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "y-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), yOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), yOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "z-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), zOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), zOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Dist. Fr Origin")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), dist_lenScalarOrder());
                }
            }
            for (size_t i = 0; i < point3DList.size(); i++) {
                cout << point3DList[i];
            }
            cout << endl << endl;
        }
    } else {
        cout << "NO INPUT FILE HAS BEEN CONFIGURED. RETURNING TO MAIN MENU..." << endl << endl;
    }
}

void store(const string& fileCrit, const string& sortCrit, const string& sortOrd, const bool& configured) {
    if (configured) {
        string textFile;
        ofstream outFile;
        size_t size = equalsIgnoreCase(fileCrit, "Line2D") ? line2DList.size()
                    : equalsIgnoreCase(fileCrit, "Line3D") ? line3DList.size()
                    : equalsIgnoreCase(fileCrit, "Point2D") ? point2DList.size()
                    : point3DList.size();

        cout << endl << "Please enter filename: ";
        cin >> textFile;

        if (textFile.find(".txt") == string::npos)
            textFile += ".txt";

        if (equalsIgnoreCase(fileCrit, "Line2D")) {
            if (equalsIgnoreCase(sortCrit, "Pt. 1")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), pt1Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line2DList.rbegin(), line2DList.rend(), pt1Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Pt. 2")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), pt2Order());
                }
                else {
                    sort(line2DList.rbegin(), line2DList.rend(), pt2Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Length")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line2DList.begin(), line2DList.end(), dist_lenScalarOrder());
                }
                else {
                    sort(line2DList.rbegin(), line2DList.rend(), dist_lenScalarOrder());
                }
            }

            outFile.open(textFile);
            outFile << right << setw(1) << " " << "P1-X" << right << setw(2) << " " << "P1-Y"
                << right << setw(5) << " " << "P2-X" << right << setw(2) << " " << "P2-Y"
                << right << setw(4) << " " << "Length" << endl;
            outFile << "- - - - - - - - - - - - - - - - - - - " << endl;

            for (size_t i = 0; i < line2DList.size(); i++) {
                outFile << line2DList[i];
            }
            outFile.close();
        }

        if (equalsIgnoreCase(fileCrit, "Line3D")) {
            if (equalsIgnoreCase(sortCrit, "Pt. 1")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), pt1Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), pt1Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Pt. 2")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), pt2Order());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), pt2Order());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Length")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(line3DList.begin(), line3DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(line3DList.rbegin(), line3DList.rend(), dist_lenScalarOrder());
                }
            }
            outFile.open(textFile);
            outFile << right << setw(1) << " " << "P1-X" << right << setw(2) << " " << "P1-Y" << right << setw(2) << " " << "P1-Z"
                << right << setw(5) << " " << "P2-X" << right << setw(2) << " " << "P2-Y" << right << setw(2) << " " << "P2-Z"
                << right << setw(4) << " " << "Length" << endl;
            outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
            for (size_t i = 0; i < line3DList.size(); i++) {
                outFile << line3DList[i];
            }
            outFile.close();
        }

        if (equalsIgnoreCase(fileCrit, "Point2D")) {
            if (equalsIgnoreCase(sortCrit, "x-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), xOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), xOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "y-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), yOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), yOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Dist. Fr Origin")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point2DList.begin(), point2DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point2DList.rbegin(), point2DList.rend(), dist_lenScalarOrder());
                }
            }
            outFile.open(textFile);
            outFile << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(4) << " " << "Dist. Fr Origin" << endl;
            outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
            for (size_t i = 0; i < point2DList.size(); i++) {
                outFile << point2DList[i];
            }
            outFile.close();
        }

        if (equalsIgnoreCase(fileCrit, "Point3D")) {
            if (equalsIgnoreCase(sortCrit, "x-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), xOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), xOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "y-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), yOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), yOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "z-ordinate")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), zOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), zOrder());
                }
            }

            if (equalsIgnoreCase(sortCrit, "Dist. Fr Origin")) {
                if (equalsIgnoreCase(sortOrd, "ASC")) {
                    sort(point3DList.begin(), point3DList.end(), dist_lenScalarOrder());
                }
                if (equalsIgnoreCase(sortOrd, "DSC")) {
                    sort(point3DList.rbegin(), point3DList.rend(), dist_lenScalarOrder());
                }
            }
            outFile.open(textFile);
            outFile << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(6) << "Z" << right << setw(4) << " " << "Dist. Fr Origin" << endl;
            outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
            for (size_t i = 0; i < point3DList.size(); i++) {
                outFile << point3DList[i];
            }
            outFile.close();
        }

        cout << endl << size << " records output successfully!" << endl << endl;
    }
    else {
        cout << "NO INPUT FILE HAS BEEN CONFIGURED. RETURNING TO MAIN MENU..." << endl << endl;
    }
    
}

void prompter(const int& choice) {
    switch (choice) {
        case 1:
        case 6:
            cout << "Going back to main menu ..." << endl << endl;
            break;

        case 2:
        case 3:
        case 4:
            cout << "..." << endl << endl;
            break;

        case 5:
            cout << "Press any key to go back to main menu ..." << endl;
            cin.get();
            cin.get();
            break;
    }
}