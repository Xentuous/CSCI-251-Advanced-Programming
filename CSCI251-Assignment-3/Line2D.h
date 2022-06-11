#ifndef LINE2D_H
#define LINE2D_H

#include <iostream>
#include "Point2D.h"

using namespace std;

class Line2D {
	friend ostream& operator<< (ostream& cout, const Line2D& l);

	protected:
		double length{};
		virtual void setLength();

	private:
		Point2D pt1;
		Point2D pt2;

	public:
		Line2D(Point2D pt1, Point2D pt2);
		~Line2D();
		Line2D();

		Point2D getPt1() const;
		Point2D getPt2() const;
		double getScalarValue() const;

		void setPt1(Point2D pt1);
		void setPt2(Point2D pt2);
		bool operator== (const Line2D& l) const;
};

#endif // !LINE2D_H
