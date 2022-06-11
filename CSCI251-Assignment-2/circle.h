#include <string>
#include <vector>
#include "shapeTwoD.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public ShapeTwoD {
	private:
		int x = 0, y = 0, radius = 0;
		vector<string> pointsInShape;
		vector<string> pointsOnShape;
		size_t index = 0;
		void setPointIOShape(vector<string> pointsInShape, vector<string> pointsOnShape);

	public:
		~Circle();
		Circle(string name, bool containsWarpSpace, int x, int y, int radius, size_t index);
		
		size_t getIndex();
		void setIndex(size_t index);

		double getArea() override;
		void setArea(double area) override;
		string toString() override;
		double computeArea() override;
		bool isPointInShape(int x, int y) override;
		bool isPointOnShape(int x, int y) override;
};

#endif // CIRCLE_H