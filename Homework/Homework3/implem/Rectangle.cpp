/*
 * Rectangle.cpp
 *
 *  Created on: Feb 9, 2022
 *      Author: aaron
 */

#include "Rectangle.h"
#include <string>


Rectangle::Rectangle(int s1, int s2) {
	// TODO Auto-generated constructor stub
	side1 = s1;
	side2 = s2;

}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}
int Rectangle::getArea(){
	 return (side1*side2);
}
int Rectangle::getPerimeter(){
	return (2*(side1+side2));
}
string Rectangle::getErrorMessage(){
	return Shape::getErrorMessage();
}
void Rectangle::setErrorMessage(string n){
	errorMessage = n;
}
