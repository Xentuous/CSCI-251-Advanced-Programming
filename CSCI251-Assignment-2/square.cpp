#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include "MinZhan.h"
#include "shapeTwoD.h"
#include "square.h"
#include "points.h"

Square::~Square() {}

Square::Square(string name, bool containsWarpSpace, vector<Points> axis, size_t index)
	  : ShapeTwoD(name, containsWarpSpace) {
	this->axis = axis;
	this->index = index;
}

void Square::sort() {
	for (int x = 0; x < 2; x++) {
		for (size_t i = 0; i < axis.size() - 1; i++) {
			for (size_t j = 0; j < axis.size() - i - 1; j++) {
				if (this->axis[j].x > this->axis[j + 1].x) {
					Points temp;
					temp.x = this->axis[j].x;
					temp.y = this->axis[j].y;

					this->axis[j].x = this->axis[j + 1].x;
					this->axis[j].y = this->axis[j + 1].y;

					this->axis[j + 1].x = temp.x;
					this->axis[j + 1].y = temp.y;
				}

				if (this->axis[j].x == this->axis[j + 1].x && this->axis[j].y > this->axis[j + 1].y) {
					Points temp;
					temp.x = this->axis[j].x;
					temp.y = this->axis[j].y;

					this->axis[j].x = this->axis[j + 1].x;
					this->axis[j].y = this->axis[j + 1].y;

					this->axis[j + 1].x = temp.x;
					this->axis[j + 1].y = temp.y;
				}
			}
		}
	}
}

void Square::getPoints() {
	sort();
	int len = 0;
	if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) > 1) {
		len = abs(this->axis[0].y - this->axis[1].y);

		for (int i = this->axis[0].x; i <= this->axis[2].x; i++) {
			for (int j = this->axis[0].y; j <= this->axis[1].y; j++) {
				if (i == this->axis[1].x || j == this->axis[1].y || i == this->axis[2].x || j == this->axis[2].y) {
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
	}
}

size_t Square::getIndex() {
	return this->index;
}

void Square::setArea(double area) {
	this->area = area;
}

double Square::getArea() {
	return this->area;
}

string Square::toString() {
	ostringstream s;
	sort();
	getPoints();

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

	if (this->pOS.size() > 0) {
		this->pOS.clear();
	}
	if (this->pIS.size() > 0) {
		this->pIS.clear();
	}
	s << endl;	
	return s.str();
}

double Square::computeArea() {
	sort();
	double val = 0.00;
	if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) == 1) {
		val = 1.00;
	} else if (this->axis[0].x == this->axis[1].x && abs(this->axis[0].y - this->axis[1].y) > 1) {
		val = pow(abs(this->axis[0].y - this->axis[1].y), 2.00);
	}

	return val;
}

bool Square::isPointInShape(int x, int y) {
	for (size_t i = 0; i < this->axis.size(); i++) {
		if (this->axis[i].x == x && this->axis[i].y == y) {
			return false;
		}
	}
	return true;
}

bool Square::isPointOnShape(int x, int y) {
	for (size_t i = 0; i < this->axis.size(); i++) {
		if (this->axis[i].x == x && this->axis[i].y == y) {
			return false;
		}
	}
	return true;
}
