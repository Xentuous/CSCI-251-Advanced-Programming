#include <string>
#include "shapeTwoD.h"
#include "points.h"

#ifndef SQUARE_H
#define SQUARE_H

using namespace std;

class Square : public ShapeTwoD {
	private:
		vector<Points> axis;
		vector<Points> pIS;
		vector<Points> pOS;
		size_t index;
		void sort();
		void getPoints();

	public:
		Square(string name, bool containsWarpSpace, vector<Points> axis, size_t index);
		~Square();

		size_t getIndex();
		
		double getArea() override;
		void setArea(double area) override;
		string toString() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
};	

#endif // !SQUARE_H
