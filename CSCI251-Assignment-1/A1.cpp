#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct cityLocStruct {
    int xGrid{};
    int yGrid{};
    int cityId{};
    string cityName;
} cityLoc;

struct cloudCovStruct {
    int xGrid;
    int yGrid;
    int ccVal;
} cloudCov;

struct pressureStruct {
    int xGrid;
    int yGrid;
    int pVal;
} pressure;

struct citySummInfoStruct {
    int cityId{};
    string cityName;
    float ACC = 0.00;
    float PR = 0.00;
    float AP = 0.00;
    char ACCSYM = ' ';
    char APSYM = ' ';
    vector<string> coOrdinates;
} citySummInfo;

void displayMenu();
void config(int& x, int& y, bool& configured);
void initialiseFile(int& x, int& y);
void storeFileData(int& checker);
void setMap(const int& x, const int& y);
void setIndex(const int& x, const int& y, const int& choice);
void setLMH(const int& x, const int& y, const int& choice);
void getPerimeter(const int& x, const int& y);
void ascii(float probRain);
void displayMap(const int& x, const int& y);
void displaySummaryReport();
void mallocFree(const int& x, const int& y);
void prompter();

char** mapPtr = nullptr;                       
string* fileData = new string[4];              
cityLocStruct* cityLocPtr = nullptr;           
cloudCovStruct* cloudCovPtr = nullptr;         
pressureStruct* pressurePtr = nullptr;         
size_t cityLocSize = 0;                        
size_t cloudCovSize = 0;                       
size_t pressureSize = 0;                       
vector<citySummInfoStruct> citySummInfoList;   

int main() {
    int choice = 0, x = 0, y = 0;
    bool configured = false;

    do {
        if (!configured) {
            config(x, y, configured);
        }
        else {
            displayMenu();
            cin >> choice;
        }

        switch (choice) {
        case 1:
            config(x, y, configured);
            break;

        case 2:
            setMap(x, y);
            cout << endl << setw(5) << " " << "[ DISPLAY CITY MAP ]" << endl << endl;
            displayMap(x, y);
            break;

        case 3:
        case 5:
            setIndex(x, y, choice);
            displayMap(x, y);
            break;

        case 4:
        case 6:
            setLMH(x, y, choice);
            displayMap(x, y);
            break;

        case 7:
            displaySummaryReport();
            break;

        case 8:
            cout << "Program has ended! " << endl;
            break;

        default:
            break;
        }
        if (choice >= 2 && choice <= 7)
            prompter();
    } while (choice != 8);
    mallocFree(x, y);
    return 0;
}

void displayMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to Weather Information Processing System" << endl;
    cout << "1)" << setw(4) << " " << "Read in and process a configuration file" << endl;
    cout << "2)" << setw(4) << " " << "Display city map" << endl;
    cout << "3)" << setw(4) << " " << "Display cloud coverage map (cloudiness index)" << endl;
    cout << "4)" << setw(4) << " " << "Display cloud coverage map (LMH symbols)" << endl;
    cout << "5)" << setw(4) << " " << "Display atmospheric pressure map (pressure index)" << endl;
    cout << "6)" << setw(4) << " " << "Display atmospheric pressure map (LMH symbols)" << endl;
    cout << "7)" << setw(4) << " " << "Show weather forecast summary report" << endl;
    cout << "8)" << setw(4) << " " << "Quit" << endl << endl;
    cout << "Please enter your choice: ";
}

void config(int& x, int& y, bool& configured) {
    char qns = ' ';

    if (configured) {
        cout << "Do you want to overwrite the " << fileData[0] << "? (Y/N): ";
        cin >> qns;

        if (qns == 'Y' || qns == 'y') {
            cout << "You are currently OVERWRITTING the current configuration file." << endl << endl;
            mallocFree(x, y);
        }
        else {
            cout << "You did NOT overwrite the current file." << endl << endl;
            prompter();
            return;
        }
    }

    do {
        cout << endl << "[ Read in and process a configuration file ]" << endl;
        cout << "Please enter config filename: ";
        if (qns == 'y' || qns == 'Y') {
            fileData = new string[4];
        }
        cin >> fileData[0];
        cout << endl;

        if (fileData[0].find(".txt") == string::npos)
            fileData[0] += ".txt";

        if (fileExists(fileData[0])) {
            initialiseFile(x, y);
            configured = true;
            qns = ' ';
        }
        else {
            cout << "File does not exist." << endl << "Do you want to try again? No to quit program. (Y/N):";
            cin >> qns;
            if (qns == 'Y' || qns == 'y') {
                delete[] fileData;
                continue;
            }
            else {
                if (qns == 'N' || qns == 'n') {
                    cout << "You have decided to quit the program." << endl;
                }
                else {
                    cout << "You have entered an invalid option. Program will now terminate." << endl;
                }
                mallocFree(x, y);
                exit(0);
            }
        }
    } while (!configured || qns == 'Y' || qns == 'y');
}

void initialiseFile(int& x, int& y) {
    ifstream readInput(fileData[0]);
    string line;
    int lineCounter = 0;
    int checker = 0;

    while (!readInput.eof()) {
        getline(readInput, line);

        if (!(line[0] == '/' && line[1] == '/') && !(line == "")) {
            if (lineCounter == 0 || lineCounter == 1) {
                char delim[] = { '=', '-' };
                vector<string> temp = tokenizer(line, delim, 2);

                if (lineCounter == 0) {
                    x = stoi(temp[2]) + 1;
                }
                else if (lineCounter == 1) {
                    y = stoi(temp[2]) + 1;
                }

                cout << "Reading in " << temp[0] << ": " << temp[1] << "-" << temp[2] << " ... done!" << endl;
                temp.clear();
                checker++;
            }
            else if (lineCounter == 2) {
                fileData[1] = line;
            }
            else if (lineCounter == 3) {
                fileData[2] = line;
            }
            else if (lineCounter == 4) {
                fileData[3] = line;
            }
            lineCounter++;
        }
    }
    cout << endl;
    readInput.close();

    mapPtr = new char* [x];

    for (int i = 0; i < x; i++) {
        mapPtr[i] = new char[y];
        for (int j = 0; j < y; j++) {
            mapPtr[i][j] = ' ';
        }
    }

    storeFileData(checker);

    if (checker == 5) {
        cout << "\nAll records successfully stored. Going back to main menu ...\n" << endl;
        getPerimeter(x, y);
    }
}

void storeFileData(int& checker) {
    for (int fD = 1; fD < 4; fD++) {
        if (fileExists(fileData[fD])) {
            string* fileDataKeeper = nullptr;
            string line, testLine;
            int keeperSize = 0, lineCounter = 0, counter = 0;;
            char delim[] = { '[', ',', ' ', ']', '-' };

            ifstream read(fileData[fD]);

            while (getline(read, testLine)) {
                keeperSize++;
            }
            read.close();
            fileDataKeeper = new string[keeperSize - 1];
            read.open(fileData[fD]);

            while (lineCounter != keeperSize - 1) {
                getline(read, line);
                fileDataKeeper[lineCounter] = line;
                lineCounter++;
            }
            read.close();

            vector<string> temp = tokenizer(fileDataKeeper, delim, 5, keeperSize - 1);
            delete[] fileDataKeeper;
            fileDataKeeper = nullptr;

            if (fD == 1) {
                cityLocSize = temp.size() / 4;
                cityLocPtr = new cityLocStruct[cityLocSize];
                for (size_t i = 0; i < temp.size(); i += 4) {
                    if (temp[i] != "" && counter < cityLocSize) {
                        cityLoc.xGrid = stoi(temp[i]);
                        cityLoc.yGrid = stoi(temp[i + 1]);
                        cityLoc.cityId = stoi(temp[i + 2]);
                        cityLoc.cityName = temp[i + 3];
                        cityLocPtr[counter] = cityLoc;
                    }
                    counter++;
                }
            }
            else if (fD == 2) {
                cloudCovSize = temp.size() / 3;
                cloudCovPtr = new cloudCovStruct[cloudCovSize];
                for (size_t i = 0; i < temp.size(); i += 3) {
                    if (temp[i] != "" && counter < cloudCovSize) {
                        cloudCov.xGrid = stoi(temp[i]);
                        cloudCov.yGrid = stoi(temp[i + 1]);
                        cloudCov.ccVal = stoi(temp[i + 2]);
                        cloudCovPtr[counter] = cloudCov;
                    }
                    counter++;
                }
            }
            else if (fD == 3) {
                pressureSize = temp.size() / 3;
                pressurePtr = new pressureStruct[pressureSize];
                for (size_t i = 0; i < temp.size(); i += 3) {
                    if (temp[i] != "" && counter < pressureSize) {
                        pressure.xGrid = stoi(temp[i]);
                        pressure.yGrid = stoi(temp[i + 1]);
                        pressure.pVal = stoi(temp[i + 2]);
                        pressurePtr[counter] = pressure;
                    }
                    counter++;
                }
            }
            temp.clear();
            cout << fileData[fD] << " ... done!" << endl;
            checker++;
        }
        else {
            cout << fileData[fD] << " not found!" << endl;
        }
    }
}

void setMap(const int& x, const int& y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (size_t k = 0; k < cityLocSize; k++) {
                if (cityLocPtr[k].xGrid == i && cityLocPtr[k].yGrid == j)
                    mapPtr[i][j] = cityLocPtr[k].cityId + '0';
            }
        }
    }
}

void setIndex(const int& x, const int& y, const int& choice) {
    size_t size = 0;
    int xGrid = 0;
    int yGrid = 0;
    int value = 0;

    switch (choice) {
    case 3:
        cout << endl << setw(5) << " " << "[ DISPLAY CLOUD COVER ]" << endl << endl;
        size = cloudCovSize;
        break;

    case 5:
        cout << endl << setw(5) << " " << "[ DISPLAY ATMOSPHERIC PRESSURE ]" << endl << endl;
        size = pressureSize;
        break;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (size_t k = 0; k < size; k++) {
                if (choice == 3) {
                    xGrid = cloudCovPtr[k].xGrid;
                    yGrid = cloudCovPtr[k].yGrid;
                    value = cloudCovPtr[k].ccVal;
                }
                else if (choice == 5) {
                    xGrid = pressurePtr[k].xGrid;
                    yGrid = pressurePtr[k].yGrid;
                    value = pressurePtr[k].pVal;
                }

                if (xGrid == i && yGrid == j) {
                    if (0 <= value && value < 10) {
                        mapPtr[i][j] = '0';
                    }
                    else if (10 <= value && value < 20) {
                        mapPtr[i][j] = '1';
                    }
                    else if (20 <= value && value < 30) {
                        mapPtr[i][j] = '2';
                    }
                    else if (30 <= value && value < 40) {
                        mapPtr[i][j] = '3';
                    }
                    else if (40 <= value && value < 50) {
                        mapPtr[i][j] = '4';
                    }
                    else if (50 <= value && value < 60) {
                        mapPtr[i][j] = '5';
                    }
                    else if (60 <= value && value < 70) {
                        mapPtr[i][j] = '6';
                    }
                    else if (70 <= value && value < 80) {
                        mapPtr[i][j] = '7';
                    }
                    else if (80 <= value && value < 90) {
                        mapPtr[i][j] = '8';
                    }
                    else if (90 <= value && value < 100) {
                        mapPtr[i][j] = '9';
                    }
                }
            }
        }
    }
}

void setLMH(const int& x, const int& y, const int& choice) {
    size_t size = 0;
    int xGrid = 0;
    int yGrid = 0;
    int value = 0;

    switch (choice) {
    case 4:
        cout << endl << setw(5) << " " << "[ DISPLAY CLOUD COVER (LMH SYMBOL) ]" << endl << endl;
        size = cloudCovSize;
        break;

    case 6:
        cout << endl << setw(5) << " " << "[ DISPLAY ATMOSPHERIC PRESSURE (LMH SYMBOL) ]" << endl << endl;
        size = pressureSize;
        break;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (size_t k = 0; k < size; k++) {
                if (choice == 4) {
                    xGrid = cloudCovPtr[k].xGrid;
                    yGrid = cloudCovPtr[k].yGrid;
                    value = cloudCovPtr[k].ccVal;
                }
                else if (choice == 6) {
                    xGrid = pressurePtr[k].xGrid;
                    yGrid = pressurePtr[k].yGrid;
                    value = pressurePtr[k].pVal;
                }

                if (xGrid == i && yGrid == j) {
                    if (0 <= value && value < 35) {
                        mapPtr[i][j] = 'L';
                    }
                    else if (35 <= value && value < 65) {
                        mapPtr[i][j] = 'M';
                    }
                    else if (65 <= value && value < 100) {
                        mapPtr[i][j] = 'H';
                    }
                }
            }
        }
    }
}

void getPerimeter(const int& x, const int& y) {
    citySummInfo.cityId = cityLocPtr[0].cityId;
    citySummInfo.cityName = cityLocPtr[0].cityName;
    citySummInfoList.push_back(citySummInfo);

    for (size_t i = 0; i < cityLocSize; i++) {
        for (size_t j = 0; j < citySummInfoList.size(); j++) {
            if (cityLocPtr[i].cityId == citySummInfoList[j].cityId && cityLocPtr[i].cityName == citySummInfoList[j].cityName) {
                break;
            }
            else if (j == citySummInfoList.size() - 1) {
                citySummInfo.cityId = cityLocPtr[i].cityId;
                citySummInfo.cityName = cityLocPtr[i].cityName;
                citySummInfoList.push_back(citySummInfo);
            }
        }
    }

    setMap(x, y);

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        for (size_t j = 0; j < cityLocSize; j++) {
            if (citySummInfoList[i].cityId == cityLocPtr[j].cityId)
                citySummInfoList[i].coOrdinates.push_back(to_string(cityLocPtr[j].xGrid) + "." + to_string(cityLocPtr[j].yGrid));
        }
    }

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        vector<string> temp;
        for (size_t j = 0; j < citySummInfoList[i].coOrdinates.size(); j++) {
            char cityId = citySummInfoList[i].cityId + '0';
            char delim[] = { '.' };
            vector<string> tempAxis = tokenizer(citySummInfoList[i].coOrdinates[j], delim, 1);

            int xAxis = stoi(tempAxis[0]);
            int yAxis = stoi(tempAxis[1]);

            if (xAxis - 1 < 0 || yAxis - 1 < 0 || xAxis + 1 >= x || yAxis + 1 >= y) {
                continue;
            }

            if (mapPtr[xAxis - 1][yAxis + 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis - 1) + "." + to_string(yAxis + 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis - 1][yAxis] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis - 1) + "." + to_string(yAxis);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis - 1][yAxis - 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis - 1) + "." + to_string(yAxis - 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis][yAxis + 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis) + "." + to_string(yAxis + 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis][yAxis - 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis) + "." + to_string(yAxis - 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis + 1][yAxis + 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis + 1) + "." + to_string(yAxis + 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis + 1][yAxis] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis + 1) + "." + to_string(yAxis);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
            if (mapPtr[xAxis + 1][yAxis - 1] != cityId) {
                if (xAxis + 1 == x || yAxis + 1 == y || xAxis - 1 < 0 || yAxis - 1 < 0)
                    continue;
                string coOrd = to_string(xAxis + 1) + "." + to_string(yAxis - 1);
                if (containString(temp, coOrd)) {
                    temp.push_back(coOrd);
                }
            }
        }
        citySummInfoList[i].coOrdinates.reserve(temp.size());
        citySummInfoList[i].coOrdinates.insert(citySummInfoList[i].coOrdinates.end(), temp.begin(), temp.end());
        temp.clear();
    }
}

void displayMap(const int& x, const int& y) {
    cout << setw(3) << " ";
    for (int header = 0; header < x + 2; header++) {
        cout << "#  ";
    }
    cout << endl;

    for (int i = y - 1; i >= 0; i--) {
        cout << left << setw(3) << i << right << setw(2) << "* ";
        for (int j = 0; j < x; j++) {
            cout << " " << mapPtr[j][i] << " ";
        }
        cout << " *" << endl;
    }

    cout << setw(3) << " ";
    for (int header = 0; header < x + 2; header++) {
        cout << "#  ";
    }
    cout << endl << setw(6) << " ";
    for (int i = 0; i < x; i++) {
        cout << i << "  ";
    }
    cout << endl << endl;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            mapPtr[i][j] = ' ';
        }
    }
}

void displaySummaryReport() {
    cout << endl << "Weather Forecast Summary Report" << endl;
    cout << "--------------------------------------" << endl;

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        sort(citySummInfoList[i].coOrdinates.begin(), citySummInfoList[i].coOrdinates.end());
        citySummInfoList[i].coOrdinates.erase(unique(citySummInfoList[i].coOrdinates.begin(), citySummInfoList[i].coOrdinates.end()),
            citySummInfoList[i].coOrdinates.end());
    }

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        float sum = 0;
        for (size_t j = 0; j < citySummInfoList[i].coOrdinates.size(); j++) {
            char cityId = citySummInfoList[i].cityId + '0';
            char delim[] = { '.' };
            vector<string> temp = tokenizer(citySummInfoList[i].coOrdinates[j], delim, 1);
            int xAxis = stoi(temp[0]);
            int yAxis = stoi(temp[1]);

            for (size_t k = 0; k < cloudCovSize; k++) {
                if (cloudCovPtr[k].xGrid == xAxis && cloudCovPtr[k].yGrid == yAxis) {
                    sum += cloudCovPtr[k].ccVal;
                }
            }
            temp.clear();
        }
        citySummInfoList[i].ACC = sum / citySummInfoList[i].coOrdinates.size();
    }

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        float sum = 0;
        for (size_t j = 0; j < citySummInfoList[i].coOrdinates.size(); j++) {
            char delim[] = { '.' };
            vector<string> temp = tokenizer(citySummInfoList[i].coOrdinates[j], delim, 1);
            int xAxis = stoi(temp[0]);
            int yAxis = stoi(temp[1]);

            for (size_t k = 0; k < pressureSize; k++) {
                if (pressurePtr[k].xGrid == xAxis && pressurePtr[k].yGrid == yAxis) {
                    sum += pressurePtr[k].pVal;
                }
            }
            temp.clear();
        }
        citySummInfoList[i].AP = sum / citySummInfoList[i].coOrdinates.size();
    }

    for (size_t i = 0; i < citySummInfoList.size(); i++) {
        if (0 <= citySummInfoList[i].ACC && citySummInfoList[i].ACC < 35) {
            citySummInfoList[i].ACCSYM = 'L';
        }
        else if (35 <= citySummInfoList[i].ACC && citySummInfoList[i].ACC < 65) {
            citySummInfoList[i].ACCSYM = 'M';
        }
        else if (65 <= citySummInfoList[i].ACC && citySummInfoList[i].ACC < 100) {
            citySummInfoList[i].ACCSYM = 'H';
        }

        if (0 <= citySummInfoList[i].AP && citySummInfoList[i].AP < 35) {
            citySummInfoList[i].APSYM = 'L';
        }
        else if (35 <= citySummInfoList[i].AP && citySummInfoList[i].AP < 65) {
            citySummInfoList[i].APSYM = 'M';
        }
        else if (65 <= citySummInfoList[i].AP && citySummInfoList[i].AP < 100) {
            citySummInfoList[i].APSYM = 'H';
        }

        if (citySummInfoList[i].APSYM == 'L' && citySummInfoList[i].ACCSYM == 'H') {
            citySummInfoList[i].PR = 90;
        }
        else if (citySummInfoList[i].APSYM == 'L' && citySummInfoList[i].ACCSYM == 'M') {
            citySummInfoList[i].PR = 80;
        }
        else if (citySummInfoList[i].APSYM == 'L' && citySummInfoList[i].ACCSYM == 'L') {
            citySummInfoList[i].PR = 70;
        }
        else if (citySummInfoList[i].APSYM == 'M' && citySummInfoList[i].ACCSYM == 'H') {
            citySummInfoList[i].PR = 60;
        }
        else if (citySummInfoList[i].APSYM == 'M' && citySummInfoList[i].ACCSYM == 'M') {
            citySummInfoList[i].PR = 50;
        }
        else if (citySummInfoList[i].APSYM == 'M' && citySummInfoList[i].ACCSYM == 'L') {
            citySummInfoList[i].PR = 40;
        }
        else if (citySummInfoList[i].APSYM == 'H' && citySummInfoList[i].ACCSYM == 'H') {
            citySummInfoList[i].PR = 30;
        }
        else if (citySummInfoList[i].APSYM == 'H' && citySummInfoList[i].ACCSYM == 'M') {
            citySummInfoList[i].PR = 20;
        }
        else if (citySummInfoList[i].APSYM == 'H' && citySummInfoList[i].ACCSYM == 'L') {
            citySummInfoList[i].PR = 10;
        }

        cout << "City Name" << setw(2) << " " << ": " << citySummInfoList[i].cityName << endl;
        cout << "City ID" << setw(4) << " " << ": " << citySummInfoList[i].cityId << endl;
        cout << "Ave. Cloud Cover" << setw(2) << " " << "(ACC)" << setw(5) << " " << ": " << fixed << setprecision(2) << citySummInfoList[i].ACC << " (" << citySummInfoList[i].ACCSYM << ")" << endl;
        cout << "Ave. Pressure" << setw(5) << " " << "(AP)" << setw(6) << " " << ": " << fixed << setprecision(2) << citySummInfoList[i].AP << " (" << citySummInfoList[i].APSYM << ")" << endl;
        ascii(citySummInfoList[i].PR);
    }
}

void ascii(float probRain) {
    cout << "Probability of Rain (%)" << setw(5) << " " << ": " << setprecision(2) << probRain << endl;
    if (probRain >= 90) {
        cout << "~~~~" << endl << "~~~~~" << endl << "\\\\\\\\\\" << endl << endl;
    }
    else if (probRain >= 80 && probRain < 90) {
        cout << "~~~~" << endl << "~~~~~" << endl << " \\\\\\\\" << endl << endl;
    }
    else if (probRain >= 70 && probRain < 80) {
        cout << "~~~~" << endl << "~~~~~" << endl << "  \\\\\\" << endl << endl;
    }
    else if (probRain >= 60 && probRain < 70) {
        cout << "~~~~" << endl << "~~~~~" << endl << "   \\\\" << endl << endl;
    }
    else if (probRain >= 50 && probRain < 60) {
        cout << "~~~~" << endl << "~~~~~" << endl << "     \\" << endl << endl;
    }
    else if (probRain >= 40 && probRain < 50) {
        cout << "~~~~" << endl << "~~~~~" << endl << endl << endl;
    }
    else if (probRain >= 30 && probRain < 40) {
        cout << "~~~" << endl << "~~~~" << endl << endl << endl << endl << endl;
    }
    else if (probRain >= 20 && probRain < 30) {
        cout << "~~" << endl << "~~~" << endl << endl << endl;
    }
    else if (probRain >= 0 && probRain < 20) {
        cout << "~~" << endl << "~~~" << endl << endl << endl;
    }
}

void mallocFree(const int& x, const int& y) {
    if ((mapPtr != nullptr && cityLocPtr != nullptr && cloudCovPtr != nullptr && pressurePtr != nullptr)) {
        for (int i = 0; i < x; i++) {
            delete[] mapPtr[i];
        }

        delete[] fileData;
        delete[] mapPtr;
        delete[] cityLocPtr;
        delete[] cloudCovPtr;
        delete[] pressurePtr;
        citySummInfoList.clear();
        fileData = nullptr;
        mapPtr = nullptr;
        cityLocPtr = nullptr;
        cloudCovPtr = nullptr;
        pressurePtr = nullptr;
    }
    else {
        delete[] fileData;
        return;
    }
}

/** The `prompter()` function prompts the user to press the <Enter> key to go back
    to the main menu.
    @return void
*/
void prompter() {
    char enter = ' ';

    do {
        cout << "Press <Enter> to go back to main menu ...";
        cin.clear();
        cin.ignore(256, '\n');
        enter = cin.get();
    } while (enter != '\n');
    cout << endl << endl;
}
