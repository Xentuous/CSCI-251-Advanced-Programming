#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H
#include <cmath>

template <typename T>
double scalar_difference(const T& first, const T& second) {
	return abs(first.getScalarValue() - second.getScalarValue());
}

template <typename T>
bool equals(const T& first, const T& second) {
	return first == second;
}

#endif // !MYTEMPLATES_H