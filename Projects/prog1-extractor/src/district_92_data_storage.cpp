/*
 * 	district_92_data_storage.cpp
 *  Created on: Feb 1, 2022
 *  Author: Aaron King
 */
#include <string>
#include "representative92.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;
string inputFile = "data/district_92_data.txt";

representative r1;
stringstream ss;

//variables below are used in parsing of information.
const char delimiter = ',';
string tempString1;
string tempString2;
string tempString3;

void tokenize(string s, string del = " ") //assumes string has 2 delimiters which are commas, will be changed soon. Based on https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
{
    int start = 0;
    int end = s.find(del);
    int count = 0;
    while (end != -1) {
    	if(count == 0)
        	tempString1 = s.substr(start, end - start);
    	else if(count == 1)
    		tempString2 = s.substr(start, end - start);
        start = end + del.size();
        end = s.find(del, start);
        count ++;
    }
    tempString3 = s.substr(start, end - start);
}

void processInput() //takes file input and assigns the incoming values to their counterparts in the default-constructed representative r1.
{
	if(inputFile != "") //if an input file is given
	{
		ifstream input (inputFile);
		string line;
		if(input.is_open())
		{
			 while (getline(input, line)) {// parse by header
				 stringstream lineStream(line); //separating the header into its own string
				 string word;
				 lineStream >> word;

				 size_t space_pos = line.find(" ");    // removes the header from the current line for line processing
				 if (space_pos != std::string::npos) {
				   line = line.substr(space_pos + 1);
				 }

				 //for each header, perform a specific action on the line
				 if(word == "PERS"){ //personal info, service info, party, county, and district are all a simple string.
					 if(r1.getPersonalInfo()=="none")
						 r1.personalInfo = "";
					 r1.personalInfo += line + "\n";
				 }
				 else if(word == "SERV"){	//service
					 if(r1.getService()=="none")
						 r1.service = "";
					 r1.service += line + "\n";
				 }
				 else if(word == "PART")	//party
					 r1.party = line;
				 else if(word == "COUN")	//county
					 r1.county = line;
				 else if(word == "DIST")	//district
					 r1.district = line;

				 else if(word == "NAME"){ //assumes 4 part name given: title, first, mid, last (this will soon be changed to accommodate 3 part names: title, first, last)
					 if(r1.name.getFirstName() == "none" || r1.name.getTitle() == "none" || r1.name.getLastName() == "none" || r1.name.getMidInit() == "none")
						 r1.name.title = r1.name.firstName = r1.name.lastName = r1.name.midInit = "";

					 	stringstream lineStream(line); //open the line stream, and use the position of the word to determine what part of the name it is
			 			int wordCount = 0;
			 			string temp;

			 			while (lineStream >> temp) {
			 				if(wordCount == 0)
			 					r1.name.title = temp;
			 				else if(wordCount==1)
			 					r1.name.firstName = temp;
			 				else if(wordCount==2)
			 					r1.name.midInit = temp;
			 				else if(wordCount==3)
			 					r1.name.lastName = temp;
			 				wordCount++;
			 			}

				 }//end else if
				 else if(word == "HOPH"){		//"Home Phone"
					 istringstream iss(line);	//open the string stream and separate the integer characters into the parts of the phone number.
					 char(c);
					 int charcount = 0;
					 int y;
					 string temp1,temp2,temp3 ="";
					 while ( iss >> c) {
					      if(isdigit(c)){//if character is a number
					    	  if(charcount >=0 && charcount <=2){	//characters 1-3 are the area code
					    		  y = c-'0';
					    		  temp1 += to_string(y);
					    	  }
					    	  else if(charcount >=3 && charcount <=5){ //characters 4-6 are the first remaining set
					    		  y = c-'0';
					    		  temp2 += to_string(y);
					    	  }
					    	  else if(charcount >=6 && charcount <=10){	//characters 7-10 are the last remaining set
					    		  y = c-'0';
					    		  temp3 += to_string(y);
					    	  }
					    	  charcount++;
					      }
					      //parts of the phone number are set below using the variables that were created above.
					      ss.clear();
					      ss << temp1;
					      ss >> r1.homephone.areaCode;
					      ss.clear();
					      ss << temp2;
					      ss >> r1.homephone.remainder1;
					      ss.clear();
					      ss << temp3;
					      ss >> r1.homephone.remainder2;

					   }
				 } //end while
				 else if(word == "BUPH"){		//"Business Phone" follows the same format as home phone number (see above)
					 istringstream iss(line);
					 char(c);
					 int charcount = 0;
					 int y;
					 string temp1,temp2,temp3 ="";
					 while ( iss >> c) {
					      if(isdigit(c)){//if character is a number
					    	  if(charcount >=0 && charcount <=2){
					    		  y = c-'0';
					    		  temp1 += to_string(y);
					    	  }
					    	  else if(charcount >=3 && charcount <=5){
					    		  y = c-'0';
					    		  temp2 += to_string(y);
					    	  }
					    	  else if(charcount >=6 && charcount <=10){
					    		  y = c-'0';
					    		  temp3 += to_string(y);
					    	  }
					    	  charcount++;
					      }
					      ss.clear();
					      ss << temp1;
					      ss >> r1.businessPhone.areaCode;
					      ss.clear();
					      ss << temp2;
					      ss >> r1.businessPhone.remainder1;
					      ss.clear();
					      ss << temp3;
					      ss >> r1.businessPhone.remainder2;
					 }//end while
				 }
				 else if(word == "HOAD"){		//"Home Address" if the line is an address, parse the line based on the delimiter "," using the tokenize function and the tempString variables. Set these pieces to the street address, city, and zipcode respectively.
					 istringstream iss(line);
					 tokenize(line, ",");
					 r1.homeAddress.streetAdd = tempString1;
					 r1.homeAddress.city = tempString2;
					 ss.clear();
					 ss << tempString3;
					 ss >> r1.homeAddress.zip;
				 }
				else if(word == "BUAD"){		//"Business Address" follows the same structure as home address above.
					 istringstream iss(line);
					 tokenize(line, ",");
					 r1.businessAddress.streetAdd = tempString1;
					 r1.businessAddress.city = tempString2;
					 ss.clear();
					 ss << tempString3;
					 ss >> r1.businessAddress.zip;
				 }
			 }

			input.close();
		}
		else
		{
			 cout << "ERROR: Could not open input file. Check file name." << endl;
		}
	}
	else
	{
		cout << "ERROR: No input file found!" << endl;
	}
}//end processInput

void getFileStatistics(){	//simply gathers line statistics using loops
	int lineCount = 0;
	int characterCount = 0;
	int wordCount = 0;
	string line;
	ifstream input (inputFile);
	if(input.is_open()){
		while(getline(input, line)){
			lineCount++;
			characterCount += line.length();
			  stringstream lineStream(line);
			        while(getline(lineStream, line, ' '))
			        {
			            wordCount++;
			        }
		}
		input.close();
	}
	cout << "\nFile Statistics:\nLine Count: "+to_string(lineCount)+"\nWord Count: "+to_string(wordCount)+"\nCharacter Count: "+to_string(characterCount) << endl;
}

int main(){
	//take in district name
	string x;
	cout << "Enter District!" << endl;
	cin >> x;

	//if correct name is given, output the info stored in representative r1. This is simply for visual purposes.
	if(x =="92"||"Berkeley"||"Berkeley County"){
		processInput();
		cout << r1.name.getFullName() + "\n" + r1.getParty() + "\n" + r1.getCounty() + "\n" + r1.getDistrict() + "\n" + r1.businessAddress.getAddress() + "\n" + r1.businessPhone.getPhoneNumber() + "\n" + r1.homeAddress.getAddress() + "\n" + r1.homephone.getPhoneNumber() + "\n\n" + r1.getPersonalInfo() + "\n" + r1.getService() << endl;
		//output the file statistics!
		getFileStatistics();
	}
	else
		cout << "I'm sorry, I don't have info on that district!";

}
