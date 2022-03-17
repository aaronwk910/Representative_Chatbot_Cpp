/*
 * FactorialFun.cpp
 *
 *  Created on: Mar 15, 2022
 *      Author: Aaron King
 */
#include <string>
#include <iostream>
#include <chrono>
using namespace std;
double combo=0;
double findfac(double n){
	double factorial = 1.0;
    for(int i = 1; i <= n; ++i)
       factorial *= i;
    return factorial;
}
void combination(double n, double r){
	try{
	if(n<=r)
		throw "First parameter must be greater than second parameter for combination to succeed.";
	double nfac = findfac(n);
	double rfac = findfac(r);
	double cfac = findfac(n-r);
	combo = (nfac/(rfac*cfac));
	}catch (const char* msg) {
	     cerr << msg << endl;
	}
}

int main(int argc, char *argv[]){ //takes argument 1 or 2 for operation and calls the other functions
	auto start = std::chrono::steady_clock::now();
	if (argc == 1){
		cout << "No argument passed." << endl;
		return 1;
	}
	else if (argc == 2){
		try{
			if(!isdigit(*argv[1])||*argv[1]-48==0)
				throw "Inputs must be numeric, nonzero, and positive.";
			string s1(argv[1]);
			double arg = stod(s1);
			cout << findfac(arg) << endl;
		}catch (const char* msg) {
		     cerr << msg << endl;
		}
	}
	else if (argc == 3){
		try{
			if(!isdigit(*argv[1])||!isdigit(*argv[2])||*argv[1]-48==0||*argv[2]-48==0)
				throw "Inputs must be numeric, nonzero, and positive.";
			string s1(argv[1]);
			string s2(argv[2]);
			double arg1 = stod(s1);
			double arg2 = stod(s2);
			combination(arg1,arg2);
			if(combo!=0)
				cout << combo << endl;
		}catch (const char* msg) {
		     cerr << msg << endl;
		}
	}
	else{
		try{
			throw "Too many arguments!";
		}catch(const char* msg) {
			cerr << msg << endl;
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff_in_seconds = end - start;
	cout << "Time for processing: " << diff_in_seconds.count() << "s\n";
	return 0;
}


