/*
 * Triangle.cpp
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#include "Triangle.h"

Triangle::Triangle(int i, int j, int k) {
	// TODO Auto-generated constructor stub
	side1 = i;
	side2 = j;
	side3 = k;
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

int Triangle::getPerimeter(){
	return (side1+side2+side3);
}
void Triangle::setErrorMessage(string n){
	errorMessage = n;
}
string Triangle::getErrorMessage(){
	return Shape::getErrorMessage();
}
