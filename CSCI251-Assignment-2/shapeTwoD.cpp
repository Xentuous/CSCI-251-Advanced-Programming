#include <string>
#include "shapeTwoD.h"
#include "MinZhan.h"

ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace) {
	this->name = name;
	this->containsWarpSpace = containsWarpSpace;
}

void ShapeTwoD::setName(string name) {
	this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
	this->containsWarpSpace = containsWarpSpace;
}

bool ShapeTwoD::getContainsWarpSpace() {
	return this->containsWarpSpace;
}

string ShapeTwoD::getName() {
	return this->name;
}

double ShapeTwoD::getArea() {
	return this->area;
}

void ShapeTwoD::setArea(double area) {
	this->area = area;
}

string ShapeTwoD::toString() {
	return "";
}

double ShapeTwoD::computeArea() {
	return 1.0;
}

bool ShapeTwoD::isPointInShape(int x, int y) {
	return false;
}

bool ShapeTwoD::isPointOnShape(int x, int y) {
	return false;
}