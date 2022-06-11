#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "Line2D.h"

void Line2D::setLength() {
	this->length = sqrt(pow(this->pt1.getX() - this->pt2.getX(), 2) + pow(this->pt1.getY() - this->pt2.getY(), 2));
}

Line2D::Line2D(Point2D pt1, Point2D pt2) {
	this->pt1 = pt1;
	this->pt2 = pt2;
	this->setLength();
}

Line2D::~Line2D() {}
Line2D::Line2D() {}

Point2D Line2D::getPt1() const {
	return this->pt1;
}

Point2D Line2D::getPt2() const {
	return this->pt2;
}

double Line2D::getScalarValue() const {
	return this->length;
}

void Line2D::setPt1(Point2D pt1) {
	this->pt1 = pt1;
}

void Line2D::setPt2(Point2D pt2) {
	this->pt2 = pt2;
}

bool Line2D::operator== (const Line2D& l) const {
	return this->getPt1() == l.getPt1() && this->getPt2() == l.getPt2();
}

ostream& operator<< (ostream& cout, const Line2D& l) {
	cout << "[" << right << setw(4) << l.getPt1().getX() << ", "
		<< right << setw(4) << l.getPt1().getY() << "]" << setw(3) << " "
		<< "[" << right << setw(4) << l.getPt2().getX() << ", "
		<< right << setw(4) << l.getPt2().getY() << "]"
		<< setw(3) << " " << fixed << setprecision(3) << l.getScalarValue()
		<< endl;

	return cout.flush();
}
