/*
 * Rectangle.h
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

class Rectangle: public Shape {
protected:
	int side1;
	int side2;
public:
	Rectangle(int, int);
	virtual ~Rectangle();
	int getArea();
	int getPerimeter();
	string getErrorMessage();
	void setErrorMessage(string);
};

#endif /* RECTANGLE_H_ */
