/*
 * Triangle.h
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_


#include "Shape.h"
class Triangle: public Shape {

protected:
	int side1;
	int side2;
	int side3;
public:
	Triangle(int, int, int);
	virtual ~Triangle();
	int getPerimeter();
	string getErrorMessage();
	void setErrorMessage(string);
};

#endif /* TRIANGLE_H_ */
