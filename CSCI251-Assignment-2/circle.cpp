#include <cmath>
#include "shapeTwoD.h"
#include "circle.h"
#include <sstream>
#include <iomanip>
#include <math.h>

Circle::~Circle() {};

Circle::Circle(string name, bool containsWarpSpace, int x, int y, int radius, size_t index) 
	  : ShapeTwoD(name, containsWarpSpace) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->index = index;
	this->area = 0;
}

size_t Circle::getIndex() {
	return this->index;
}

void Circle::setIndex(size_t index) {
	this->index = index;
}

string Circle::toString() {
	ostringstream s;

	s << "Shape [" << getIndex() << "]" <<
		"\nName: " << getName() <<
		"\nSpecial Type: " << (getContainsWarpSpace() ? "WS" : "NS") <<
		"\nArea: " << fixed << setprecision(2) << getArea() << " units square" << endl;
	
	setPointIOShape(this->pointsInShape, this->pointsOnShape);

	s << endl << "Points on perimeter: ";
	if (this->pointsOnShape.size() == 0) {
		s << "NIL" << endl;
	}
	else {
		for (size_t i = 0; i < this->pointsOnShape.size(); i++) {
			i == this->pointsOnShape.size() - 1 ? s << this->pointsOnShape[i] << endl : s << this->pointsOnShape[i] << ", ";
		}
		this->pointsOnShape.clear();
	}

	s << endl << "Points within shape: ";
	if (this->pointsInShape.size() == 0) {
		s << "NIL" << endl;
	}
	else {
		for (size_t i = 0; i < this->pointsInShape.size(); i++) {
			i == this->pointsInShape.size() - 1 ? s << this->pointsInShape[i] << endl : s << this->pointsInShape[i] << ", ";
		}
		this->pointsInShape.clear();
	}
	
	return s.str();
}

double Circle::computeArea() {
	return (2 * acos(0.0)) * pow(this->radius, 2);
}

void Circle::setArea(double area) {
	this->area = area;
}

double Circle::getArea() {
	return this->area;
}

bool Circle::isPointInShape(int x, int y) {
	return pow((x - this->x), 2) + pow((y - this->y), 2) < pow(this->radius, 2);
}

bool Circle::isPointOnShape(int x, int y) {
	return pow((x - this->x), 2) + pow((y - this->y), 2) == pow(this->radius, 2);
}
 
void Circle::setPointIOShape(vector<string> pointsInShape, vector<string> pointsOnShape) {
	for (int i = this->x - this->radius; i <= this->x + this->radius; i++) {
		for (int j = this->y - this->radius; j <= this->y + this->radius; j++) {
			if (isPointInShape(i, j)) {
				this->pointsInShape.push_back("(" + to_string(i) + ", " + to_string(j) + ")");
			}
			else if (isPointOnShape(i, j)) {
				this->pointsOnShape.push_back("(" + to_string(i) + ", " + to_string(j) + ")");
			}
		}
	}	
}
