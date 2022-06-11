#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include "Point2D.h"

using namespace std;

class Point3D : public Point2D {
	friend ostream& operator<< (ostream& cout, const Point3D& p);

	protected:
		int z{};
		void setDistFrOrigin() override;

	public:
		Point3D(int x, int y, int z);
		~Point3D();
		Point3D();

		int getZ() const ;

		void setZ(int z);
		bool operator== (const Point3D& p) const;
};

#endif // !POINT3D_H
