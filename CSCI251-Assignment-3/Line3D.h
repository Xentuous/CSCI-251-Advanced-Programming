#ifndef LINE3D_H
#define LINE3D_H

#include <iostream>
#include "Line2D.h"
#include "Point3D.h"

using namespace std;

class Line3D : public Line2D {
	friend ostream& operator<<(ostream& cout, const Line3D& l);

	protected:
		void setLength() override;

	private:
		Point3D pt1;
		Point3D pt2;

	public:
		Line3D(Point3D pt1, Point3D pt2);
		~Line3D();
		Line3D();

		Point3D getPt1() const;
		Point3D getPt2() const;

		void setPt1(Point3D pt1);
		void setPt2(Point3D pt2);

		bool operator== (const Line3D& l) const;
};

#endif // !LINE3D_H