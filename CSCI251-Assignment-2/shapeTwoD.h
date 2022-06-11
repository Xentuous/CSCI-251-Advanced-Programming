#include <string>

#ifndef SHAPETWOD_H
#define SHAPETWOD_H

using namespace std;

class ShapeTwoD {
	protected:
		string name;
		bool containsWarpSpace;
		double area = 0;

	public:
		ShapeTwoD(string name, bool containWarpSpace);

		void setName(string name);
		void setContainsWarpSpace(bool containsWarpSpace);
		string getName();
		bool getContainsWarpSpace();

		virtual ~ShapeTwoD() {};
		virtual double getArea();
		virtual void setArea(double area);
		virtual string toString();
		virtual double computeArea();
		virtual bool isPointInShape(int x, int y);
		virtual bool isPointOnShape(int x, int y);
};
#endif // !SHAPETWOD_H
