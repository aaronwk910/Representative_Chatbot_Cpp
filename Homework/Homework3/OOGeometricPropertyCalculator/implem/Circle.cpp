/*
 * Circle.cpp
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */
#include <math.h>
#include "Circle.h"

Circle::Circle(int i) {
	// TODO Auto-generated constructor stub
	rad = i;
}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}
double Circle::getArea(){
	return (rad*rad*M_PI);
}
double Circle::getPerimeter(){
	return (2*rad*M_PI);
}
void Circle::setErrorMessage(string n){
	errorMessage = n;
}
string Circle::getErrorMessage(){
	return Shape::getErrorMessage();
}
