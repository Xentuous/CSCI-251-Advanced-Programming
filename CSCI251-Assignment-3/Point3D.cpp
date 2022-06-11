#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point3D.h"
#include "Point2D.h"

using namespace std;

void Point3D::setDistFrOrigin() {
	this->distFrOrigin = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Point3D::Point3D(int x, int y, int z) : Point2D(x, y) {
	this->z = z;
	this->setDistFrOrigin();
}

Point3D::~Point3D() {}

Point3D::Point3D() {}

int Point3D::getZ() const {
	return this->z;
}

void Point3D::setZ(int z) {
	this->z = z;
}

bool Point3D::operator==(const Point3D& p) const {
	return this->x == p.getX() && this->y == p.getY() && this->z == p.getZ();
}

ostream& operator<<(ostream& cout, const Point3D& p) {
	cout << "["
		<< right << setw(4) << p.getX() << ", "
		<< right << setw(4) << p.getY() << ", "
		<< right << setw(4) << p.getZ() << "]"
		<< right << setw(3) << " "
		<< fixed << setprecision(3) << p.getScalarValue()
		<< endl;
	return cout.flush();
}