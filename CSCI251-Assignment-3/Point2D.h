#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <string> 

using namespace std;

class Point2D {
	friend ostream& operator<<(ostream& cout, const Point2D& p);
	protected:
		int x{}, y{};
		double distFrOrigin{};
		virtual void setDistFrOrigin();

	public:
		Point2D(int x, int y);
		~Point2D();
		Point2D();

		int getX() const;
		int getY() const;
		double getScalarValue() const;

		void setX(int x);
		void setY(int y);

		bool operator== (const Point2D& p) const;
};


#endif // !POINT2D_H
