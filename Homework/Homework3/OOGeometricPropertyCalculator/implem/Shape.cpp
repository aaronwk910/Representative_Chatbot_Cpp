/*
 * Shape.cpp
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#include "Shape.h"

Shape::Shape() {
	// TODO Auto-generated constructor stub
	area = 0;
	perimeter = 0;
	errorMessage = "Error: not enough information to calculate";

}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

double Shape::getArea(){
	return area;
}
double Shape::getPerimeter(){
	return perimeter;
}
string Shape::getErrorMessage(){
	return errorMessage;
}
void Shape::setErrorMessage(string n){
	errorMessage = n;
}
