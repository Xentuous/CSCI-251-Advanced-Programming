#include <string>
#include "shapeTwoD.h"
#include "points.h"

#ifndef CROSS_H
#define CROSS_H

using namespace std;

class Cross : public ShapeTwoD {
	private:
		vector<Points> axis;
		vector<Points> pIS;
		vector<Points> pOS;
		vector<Points> sortedShapeAxis;
		size_t index;
		void sort(vector<Points>& vec);
		void getPoints();
		void getPIOS();
		void filter();
		bool isRectangle(Points p1, Points p2, Points p3, Points p4);
		bool isSquare(Points p1, Points p2, Points p3, Points p4);	

	public:
		Cross(string name, bool containsWarpSpace, vector<Points>axis, size_t index);
		~Cross();

		size_t getIndex();

		void setArea(double area) override;
		double getArea();
		string toString() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
};

#endif // !CROSS_H
