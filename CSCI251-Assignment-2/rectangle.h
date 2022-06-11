#include <string>
#include "shapeTwoD.h"
#include "points.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

using namespace std;

class Rectangle : public ShapeTwoD {
	private:
		vector<Points> axis;
		vector<Points> pIS;
		vector<Points> pOS;
		size_t index;
		void sort();
		void getPoints();

	public:
		Rectangle(string name, bool containsWarpSpace, vector<Points>axis, size_t index);
		~Rectangle();
	
		size_t getIndex();
		
		double getArea() override;
		void setArea(double area) override;
		string toString() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
};

#endif // !RECTANGLE_H