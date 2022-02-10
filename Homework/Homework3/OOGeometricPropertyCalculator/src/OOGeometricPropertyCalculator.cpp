#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

using namespace std;
string inputFile = "data/input.txt";
string outputFile = "data/output.txt";
string shapeType;
int shapeInt1 = 0;
int shapeInt2 = 0;
int shapeInt3 = 0;
string output = "";

void processInput() //takes file input and assigns the incoming values to the global variables above
{
	if(inputFile != "")
	{
		ifstream input (inputFile);
		string line;
		if(input.is_open())
		{
			 while (getline(input, line)) {
			 			// Now parse each line
			 			stringstream lineStream(line);
			 			int wordCount = 0;
			 			string word;

			 			while (lineStream >> word) {
			 				if(wordCount == 0)
			 				{
			 					std::for_each(word.begin(), word.end(), [](char & c) {c = ::toupper(c);}); //makes operation name in file case-insensitive, based on tutorial from thispointer.com
			 					shapeType = word;
			 				}
			 				else if(wordCount==1)
			 					shapeInt1 = stoi(word);
			 				else if(wordCount==2)
			 					shapeInt2 = stoi(word);
			 				else if(wordCount==3)
			 					shapeInt3 = stoi(word);
			 				wordCount++;
			 			} // end - while
			 }
			input.close();
		}
		else
		{
			cout << "check input file name" <<endl;
		}
	}
	else
	{
		cout << "No input file found!" <<endl;
	}
}//end processInput

void shapeCalc(int operation) //calculates area or perimeter for given shape and sets output string
{
	if(shapeType == "RECTANGLE")
	{
		if(shapeInt1 == 0 || shapeInt2 == 0)
			output= "Invalid shape parameters";
		else{
			Rectangle r1(shapeInt1, shapeInt2);
			if(operation == 1)
				output="RECTANGLE AREA " + to_string(r1.getArea());
			else
				output= "RECTANGLE PERIMETER " + to_string(r1.getPerimeter());
			}
	}
	else if(shapeType == "CIRCLE")
	{
		if(shapeInt1 == 0)
			output= "Invalid shape parameters";
		else{
			Circle c1(shapeInt1);
			if(operation == 1)
				output = "CIRCLE AREA " + to_string(c1.getArea());
			else
				output = "CIRCLE PERIMETER " + to_string(c1.getPerimeter());
			}
	}
	else if(shapeType == "TRIANGLE")
	{
		if(shapeInt1 == 0 || shapeInt2 == 0 || shapeInt3 == 0)
			output= "Invalid shape parameters";
		else{
			Triangle t1(shapeInt1, shapeInt2, shapeInt3);
			if(operation == 1){
				output = t1.getErrorMessage();
			}
			else
				output = "TRIANGLE PERIMETER " + to_string(t1.getPerimeter());
		}
	}
	else
		output = "Invalid shape type";
}
void processOutput() //outputs results
{
		ofstream outputstream (outputFile);
		if(outputstream.is_open())
		{
			outputstream << output << endl;
			cout << output << endl;
		}
		else //output file not opening
		{
			output = "Cannot open output file";
			cout << output << endl;
		}
	outputstream.close();
}//end processOutput

int main(int argc, char *argv[]){ //takes argument 1 or 2 for operation and calls the other functions

	char command = 0;
	cout << "Program name : " << argv[0] << endl;

	if (argc == 1){
		cout << "No command passed." << endl;
		return 1;
	}
	else{// argc >= 2
		command = *argv[1];
		cout << "Command to run is - " << command << endl;
	}

	processInput();
	if (command == '1')
		shapeCalc(1);
	else if (command == '2')
		shapeCalc(2);
	else
		output = "Invalid argument. Please choose 1 for Area or 2 for Perimeter";
	processOutput();
	return 0;
}




