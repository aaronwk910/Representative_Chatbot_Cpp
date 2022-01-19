/*
 * FileBasedCalculator.cpp
 *
 *  Created on: Jan 19, 2022
 *  Author: Aaron King
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

string operation = "none";
string inputFile = "data/input.txt";
string outputFile = "data/output.txt";
string error = "none";
int run = 0;
int num1 = 0;
int num2 = 0;
double solution = 0.0;


//calculation algorithm below
double calculate(int num1, int num2, string operation) //wondering why this returns a double? check division section below
{
	double soln = 0.0;
	if(operation == "multiply")
	{
		soln = num1*num2;
	}
	else if(operation == "divide") //will return 0 if inputs are integers, so cast them as doubles first, function must output a double
	{
		double num3 = (double)num1;
		double num4 = (double)num2;
		soln = (num3/num4);
	}
	else if(operation == "subtract")
	{
		soln = (num1-num2);
	}
	else if(operation == "add")
	{
		soln = num1+num2;
	}
	else
	{
		error = "Operation not recognized";
		run = 1;
	}
	return soln;
}

//processing file input below
void processInput()
{
	if(inputFile != "")
	{
		ifstream input (inputFile);
		string line;
		if(input.is_open())
		{
			//sort info
			 int i = 0;
			 while (getline(input, line))
			    {
			       	string output = line;
			       	if(i==0)
			       	{
			       		std::for_each(output.begin(), output.end(), [](char & c) {c = ::tolower(c);}); //makes operation name in file case-insensitive, based on tutorial from thispointer.com
			       		operation = output;
			       	}
			       	if(i==1)
			       		num1 = stoi(output); //stoi converts a string into an int
			       	if(i==2)
			       		num2 = stoi(output);
			        i++;
			    }
			input.close();

		}
		else
		{
			error = "Could not open input file. Check file name.";
			run = 1;
		}
	}
	else
	{
		error = "No input file found!";
		run = 1; //stop running
	}
}//end processInput

//process output below
void processOutput() //outputs results
{
	if(operation != "none")
	{
		ofstream output (outputFile);
		if(output.is_open())
		{//process
			output<<"The result of " << operation << " on " <<num1<< " and "<<num2<< " is below" <<endl; //print to file
			output <<solution<<endl;
			cout<<"The result of " << operation << " on " <<num1<< " and "<<num2<< " is below" <<endl; //print to console
			cout <<solution<< endl;
			output.close();
		}
		else //output file not opening
		{
			error = "Cannot open output file";
			run = 1;
		}
	}
	else //an error has occurred, original value of "operation" not overwritten
	{
		error = "Error processing input!";
		run = 1;
	}
}

int checkRun() //function to check for errors
{
	if(run==1)
	{
		cout << "Error: " <<error<< endl;
		return 1;
	}
	else
		return 0;
}

int main()
{
	processInput(); //process input file
	if(checkRun()==1) //see if an error has occurred
		return 1;

	solution = calculate(num1, num2, operation); //calculate result
	if(checkRun()==1)
		return 1;

	processOutput(); //output result to file
	if(checkRun()==1)
		return 1;

	return 0;
}


