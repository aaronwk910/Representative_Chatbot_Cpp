/*
 * Circle.h
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "Shape.h"

class Circle: public Shape{
	int rad;
public:
	Circle(int);
	double getArea();
	double getPerimeter();
	virtual ~Circle();
	string getErrorMessage();
	void setErrorMessage(string);
};

#endif /* CIRCLE_H_ */
