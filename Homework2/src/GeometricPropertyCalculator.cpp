/*
 * GeometricPropertyCalculator.cpp
 *
 *  Created on: Jan 26, 2022
 *      Author: aaron
 */
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

string inputFile = "data/input.txt";
string outputFile = "data/output.txt";
string shapeType;
int shapeInt1 = 0;
int shapeInt2 = 0;
int shapeInt3 = 0;
string output;

struct shape { //new object called shape
	string type;
	int val1; //first value passed
	int val2; //second value passed
	int val3; //third value passed
};

void processInput() //takes file input and assigns the incoming values to the global variables above
{
	if(inputFile != "")
	{
		ifstream input (inputFile);
		string line;
		if(input.is_open())
		{
			//sort info
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
			output = "ERROR: Could not open input file. Check file name.";
		}
	}
	else
	{
		output = "ERROR: No input file found!";
	}
}//end processInput

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
}//end processOutput

void shapeCalc(shape shape1, int demand) //calculates area or perimeter for given shape and sets output string
{
	if(shape1.type == "RECTANGLE")
	{
		if(shape1.val1 == 0 || shape1.val2 == 0)
			output= "ERROR: Invalid shape parameters";
		else if(demand == 1)
		{
			int area = (shape1.val1*shape1.val2);
			output= "RECTANGLE AREA " + to_string(area);
		}
		else
		{
			int perimeter = (2*(shape1.val1+shape1.val2));
			output= "RECTANGLE PERIMETER " + to_string(perimeter);
		}
	}
	else if(shape1.type == "CIRCLE")
	{
		if(shape1.val1 == 0)
			output= "ERROR: Invalid shape parameters";
		else if(demand == 1)
		{
			double area = (M_PI*(shape1.val1*shape1.val1));
			output = "CIRCLE AREA " + to_string(area);
		}
		else
		{
			double perimeter = (2*(M_PI*(shape1.val1)));
			output = "CIRCLE PERIMETER " + to_string(perimeter);
		}
	}
	else if(shape1.type == "TRIANGLE")
	{
		if(shape1.val1 == 0 || shape1.val2 == 0 || shape1.val3 == 0)
			output= "ERROR: Invalid shape parameters";
		else if(demand == 1)
		{
			output = "ERROR: Not enough information to calculate";
		}
		else
		{
			int perimeter = (shape1.val1+shape1.val2+shape1.val3);
			output = "TRIANGLE PERIMETER " + to_string(perimeter);
		}
	}
	else
		output = "ERROR: Invalid shape type";
}

int main(int argc, char *argv[]){ //takes argument 1 or 2 for operation and calls the other functions

	char command = 0;
	cout << "Program name : " << argv[0] << endl;

	if (argc == 1)
	{
		cout << "No command passed." << endl;
		return 1;
	}

	else // argc >= 2
	{
		command = *argv[1];
		cout << "Command to run is - " << command << endl;
	}

	processInput();
	shape currentShape = {shapeType, shapeInt1, shapeInt2, shapeInt3};

	if (command == '1')
		shapeCalc(currentShape, 1);
	else if (command == '2')
		shapeCalc(currentShape, 2);
	else
		output = "ERROR: Invalid argument. Please choose 1 for Area or 2 for Perimeter";

	processOutput();
	return 0;
}
