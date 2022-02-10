/*
 * Shape.h
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#ifndef SHAPE_H_
#define SHAPE_H_
#include <string>

using namespace std;

class Shape {

public:

	int area;
	int perimeter;
	string errorMessage;
	Shape();
	virtual ~Shape();

	double getArea();
	double getPerimeter();
	string getErrorMessage();
	void setErrorMessage(string);
};

#endif /* SHAPE_H_ */
