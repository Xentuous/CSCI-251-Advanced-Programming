#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include "MinZhan.h"
#include "shapeTwoD.h"
#include "cross.h"
#include "points.h"

Cross::~Cross() {}

Cross::Cross(string name, bool containsWarpSpace, vector<Points>axis, size_t index)
	 : ShapeTwoD(name, containsWarpSpace) {
	this->axis = axis;
	this->index = index;
}

void Cross::sort(vector<Points>& vec) {
	for (int x = 0; x < 2; x++) {
		for (size_t i = 0; i < vec.size() - 1; i++) {
			for (size_t j = 0; j < vec.size() - i - 1; j++) {
				if (vec[j].x > vec[j + 1].x) {
					Points temp;
					temp.x = vec[j].x;
                    temp.y = vec[j].y;

                    vec[j].x = vec[j + 1].x;
                    vec[j].y = vec[j + 1].y;

                    vec[j + 1].x = temp.x;
                    vec[j + 1].y = temp.y;
				}

				if (vec[j].x == vec[j + 1].x && vec[j].y > vec[j + 1].y) {
					Points temp;
					temp.x = vec[j].x;
                    temp.y = vec[j].y;

                    vec[j].x = vec[j + 1].x;
                    vec[j].y = vec[j + 1].y;

                    vec[j + 1].x = temp.x;
                    vec[j + 1].y = temp.y;
				}
			}
		}
	}
}

void Cross::getPoints() {
    if (!this->pOS.empty()) {
        this->pOS.clear();
    }
    if (!this->pIS.empty()) {
        this->pIS.clear();
    }

    Points temp;
    if (isSquare(axis[0], axis[1], axis[3], axis[4])) {
        
        temp.x = axis[0].x;
        temp.y = axis[0].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[1].x;
        temp.y = axis[1].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[3].x;
        temp.y = axis[3].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[4].x;
        temp.y = axis[4].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }
    if (isSquare(axis[2], axis[5], axis[6], axis[9])) {
        temp.x = axis[2].x;
        temp.y = axis[2].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[5].x;
        temp.y = axis[5].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[6].x;
        temp.y = axis[6].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[9].x;
        temp.y = axis[9].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }
    if (isSquare(axis[7], axis[8], axis[10], axis[11])) {
        temp.x = axis[7].x;
        temp.y = axis[7].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[8].x;
        temp.y = axis[8].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[10].x;
        temp.y = axis[10].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[11].x;
        temp.y = axis[11].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }

    if (isRectangle(axis[0], axis[1], axis[3], axis[4])) {
        temp.x = axis[0].x;
        temp.y = axis[0].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[1].x;
        temp.y = axis[1].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[3].x;
        temp.y = axis[3].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[4].x;
        temp.y = axis[4].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }
    if (isRectangle(axis[2], axis[5], axis[6], axis[9])) {
        temp.x = axis[2].x;
        temp.y = axis[2].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[5].x;
        temp.y = axis[5].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[6].x;
        temp.y = axis[6].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[9].x;
        temp.y = axis[9].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }
    if (isRectangle(axis[7], axis[8], axis[10], axis[11])) {
        temp.x = axis[7].x;
        temp.y = axis[7].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[8].x;
        temp.y = axis[8].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[10].x;
        temp.y = axis[10].y;
        this->sortedShapeAxis.push_back(temp);
        temp.x = axis[11].x;
        temp.y = axis[11].y;
        this->sortedShapeAxis.push_back(temp);

        getPIOS();

        temp.x = 0;
        temp.y = 0;
        this->sortedShapeAxis.clear();
    }

    sort(this->pOS);
    sort(this->axis);

    for (size_t i = 0; i < axis.size(); i++) {
        for (size_t j = 0; j < pOS.size(); j++) {
            if (pOS[j].x == axis[i].x && pOS[j].y == axis[i].y) {
                pOS.erase(pOS.begin() + j);
            }
        }
    }
}

void Cross::getPIOS() {
    for (int i = this->sortedShapeAxis[0].x; i <= this->sortedShapeAxis[2].x; i++) {
        for (int j = this->sortedShapeAxis[0].y; j <= this->sortedShapeAxis[1].y; j++) {
            if (i == this->sortedShapeAxis[1].x || j == this->sortedShapeAxis[1].y || i == this->sortedShapeAxis[2].x || j == this->sortedShapeAxis[2].y) {
                if (isPointOnShape(i, j)) {
                    Points p;
                    p.x = i;
                    p.y = j;
                    pOS.push_back(p);
                }
            }
            else {
                if (isPointInShape(i, j)) {
                    Points p;
                    p.x = i;
                    p.y = j;
                    pIS.push_back(p);
                }
            }
        }
    }
    this->sortedShapeAxis.clear();
}

void Cross::filter() {
    if (this->pIS.size() == 0) {
        return;
    }

    if (this->pOS.size() > 0) {
        sort(this->pOS);
    }

    if (this->pIS.size() > 0) {
        sort(this->pIS);
    }

    int initX = pOS[0].x, initY = pOS[0].y;
    for (size_t i = 1; i < this->pOS.size(); i++) {
        if (initX == this->pOS[i].x && initY == this->pOS[i].y) {
            Points temp;
            temp.x = initX;
            temp.y = initY;
            this->pIS.push_back(temp);
            this->pOS.erase(pOS.begin() + i);
        }
        initX = this->pOS[i].x, initY = this->pOS[i].y;
    }

    if (this->pIS.size() > 0) {
        for (size_t i = 0; i < this->pOS.size(); i++) {
            for (size_t j = 0; j < pIS.size(); j++) {
                if (this->pOS[i].x == this->pIS[j].x && this->pOS[i].y == this->pIS[j].y) {
                    this->pOS.erase(this->pOS.begin() + i);
                }
            }
        }
    }

    if (this->pOS.size() > 0) {
        sort(this->pOS);
    }

    if (this->pIS.size() > 0) {
        sort(this->pIS);
    }
}

bool Cross::isRectangle(Points p1, Points p2, Points p3, Points p4) {
    if (p1.x == p2.x && p3.x == p4.x) {
        if (p1.x - p2.x == p3.x - p4.x && p1.y - p2.y == p3.y - p4.y) {
            if (abs(p1.y - p2.y) > abs(p1.x - p3.x) || abs(p1.y - p2.y) < abs(p1.x - p3.x)) {
                return true;
            }
        }
    }

    return false;
}

bool Cross::isSquare(Points p1, Points p2, Points p3, Points p4) {
    if (p1.x == p2.x && p3.x == p4.x && p1.y == p3.y && p2.y == p4.y &&
        abs(p1.x - p3.x) == abs(p1.y - p2.y) &&
        abs(p2.y - p1.y) == abs(p2.x - p4.x) &&
        abs(p3.x - p1.x) == abs(p3.y - p4.y) &&
        abs(p4.x - p2.x) == abs(p4.y - p3.y)) {
        return true;
    }
    return false;
}

double Cross::getArea() {
    return this->area;
}

void Cross::setArea(double area) {
    this->area = area;
}

size_t Cross::getIndex() {
	return this->index;
}

string Cross::toString() {
    ostringstream s;

    sort(this->axis);
    getPoints();
    filter();
    
    s << "Shape [" << getIndex() << "]" <<
        "\nName: " << getName() <<
        "\nSpecial Type: " << (getContainsWarpSpace() ? "WS" : "NS") <<
        "\nArea: " << fixed << setprecision(2) << getArea() << " units square" <<
        "\nVertices: " << endl;

    for (size_t i = 0; i < this->axis.size(); i++)
        s << "Point [" << i << "]: (" << this->axis[i].x << ", " << this->axis[i].y << ")" << endl;
    

    s << endl << "Points on perimeter: ";
    if (this->pOS.size() == 0) {
        s << "NIL";
    }
    else {
        for (size_t i = 0; i < this->pOS.size(); i++) {
            s << "(" << this->pOS[i].x << ", " << this->pOS[i].y << "), ";
        }
        s.seekp(-2, std::ios_base::end);
    }

    s << endl << endl << "Points within shape: ";
    if (this->pIS.size() <= 0) {
        s << "NIL";
    }
    else {
        for (size_t i = 0; i < this->pIS.size(); i++) {
            s << "(" << this->pIS[i].x << ", " << this->pIS[i].y << "), ";
        }
        s.seekp(-2, std::ios_base::end);
    }

    s << endl;
	return s.str();
}

double Cross::computeArea() {
    sort(this->axis);
    double val = 0.00;

    if (isSquare(axis[0], axis[1], axis[3], axis[4])) {
        if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) == 1) {
            val += 1.00;
        }
        else if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) > 1) {
            val += pow(abs(this->axis[0].y - this->axis[1].y), 2.00);
        }
    }
    if (isSquare(axis[2], axis[5], axis[6], axis[9])) {
        if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) == 1) {
            val += 1.00;
        }
        else if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) > 1) {
            val += pow(abs(this->axis[0].y - this->axis[1].y), 2.00);
        }
    }
    if (isSquare(axis[7], axis[8], axis[10], axis[11])) {
        if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) == 1) {
            val += 1.00;
        }
        else if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) > 1) {
            val += pow(abs(this->axis[0].y - this->axis[1].y), 2.00);
        }
    }

    if (isRectangle(axis[0], axis[1], axis[3], axis[4])) {
        val += abs(this->axis[0].y - this->axis[1].y) * abs(this->axis[0].x - this->axis[3].x);
    }
    if (isRectangle(axis[2], axis[5], axis[6], axis[9])) {
        val += abs(this->axis[2].y - this->axis[5].y) * abs(this->axis[2].x - this->axis[6].x);
    }
    if (isRectangle(axis[7], axis[8], axis[10], axis[11])) {
        val += abs(this->axis[7].y - this->axis[8].y) * abs(this->axis[7].x - this->axis[10].x);
    }
    
    return val;
}

bool Cross::isPointInShape(int x, int y) {
    for (size_t i = 0; i < this->sortedShapeAxis.size(); i++) {
        if (this->sortedShapeAxis[i].x == x && this->sortedShapeAxis[i].y == y) {
            return false;
        }
    }
    return true;
}

bool Cross::isPointOnShape(int x, int y) {
    for (size_t i = 0; i < this->sortedShapeAxis.size(); i++) {
        if (this->sortedShapeAxis[i].x == x && this->sortedShapeAxis[i].y == y) {
            return false;
        }
    }
    return true;
}
