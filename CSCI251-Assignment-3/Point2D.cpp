#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "Point2D.h"

using namespace std;

void Point2D::setDistFrOrigin() {
	this->distFrOrigin = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Point2D::Point2D(int x, int y) {
	this->x = x;
	this->y = y;
	setDistFrOrigin();
}

Point2D::~Point2D() {}

Point2D::Point2D() {}

int Point2D::getX() const {
	return this->x;
}

int Point2D::getY() const {
	return this->y;
}

double Point2D::getScalarValue() const {
	return this->distFrOrigin;
}

void Point2D::setX(int x) {
	this->x = x;
}

void Point2D::setY(int y) {
	this->y = y;
}

bool Point2D::operator==(const Point2D& p) const {
	return this->x == p.getX() && this->y == p.getY();
}

ostream& operator<<(ostream& cout, const Point2D& p) {
	cout << "[" << right << setw(4) << p.getX() << ", " 
		        << right << setw(4) << p.getY() << "]" 
		        << right << setw(3) << " " 
		        << fixed << setprecision(3) << p.getScalarValue() 
		        << endl;
	return cout.flush();
}
