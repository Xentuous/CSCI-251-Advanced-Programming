#include <iostream>
#include <iomanip>
#include <cmath>
#include "Line3D.h"

using namespace std;

void Line3D::setLength() {
	this->length = sqrt(pow(this->pt1.getX() - this->pt2.getX(), 2) + pow(this->pt1.getY() - this->pt2.getY(), 2) + pow(this->pt1.getZ() - this->pt2.getZ(), 2));
}

Line3D::Line3D(Point3D pt1, Point3D pt2) {
	this->pt1 = pt1;
	this->pt2 = pt2;
	this->setLength();

}Line3D::~Line3D() {}

Line3D::Line3D() {}

Point3D Line3D::getPt1() const {
	return this->pt1;
}

Point3D Line3D::getPt2() const {
	return this->pt2;
}

void Line3D::setPt1(Point3D pt1) {
	this->pt1 = pt1;
}

void Line3D::setPt2(Point3D pt2) {
	this->pt2 = pt2;
}

bool Line3D::operator== (const Line3D& l) const {
	return this->getPt1() == l.getPt1() && this->getPt2() == l.getPt2();
}

ostream& operator<<(ostream& cout, const Line3D& l) {
	cout << "[" << right << setw(4) << l.getPt1().getX() << ", " << right << setw(4) << l.getPt1().getY() << ", " << right << setw(4) << l.getPt1().getZ() << "]"
		<< setw(3) << " "
		<< "[" << right << setw(4) << l.getPt2().getX() << ", " << right << setw(4) << l.getPt2().getY() << ", " << right << setw(4) << l.getPt2().getZ() << "]"
		<< setw(3) << " "
		<< fixed << setprecision(3) << l.getScalarValue()
		<< endl;

	return cout.flush();
}
