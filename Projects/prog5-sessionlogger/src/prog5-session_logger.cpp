/*
 * 	prog5-session_logger.cpp
 *  Created on: April 4, 2022
 *  Author: Aaron King
 */
#include <chrono>
#include <ctime>
#include <string>
#include "representative92.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <regex>
#include <numeric>
#include <algorithm>

using namespace std;
auto start = std::chrono::system_clock::now();
auto steadystart = std::chrono::steady_clock::now();
string inputFile = "data/district_92_data.txt";
string csvFile= "data/chat_statistics.csv";
string outputFile;
string ts;//timestring

representative r1;
stringstream ss;

int systemUtterance = 0;
int userUtterance = 0;
int rownumber = 0;
vector<string> row;

//variables below are used in parsing of information.
const char delimiter = ',';
string tempString1;
string tempString2;
string tempString3;
string answer = "Request not recognized. Please try again.";

void generateFileName(string s){
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	s = "";
	for(int i=0;i<3;i++){
		s+=vstrings[i]+"_";
	}
	s+=vstrings[4]+"_";
	vstrings[3].erase(remove(vstrings[3].begin(), vstrings[3].end(), ':'), vstrings[3].end());
	s+=vstrings[3]+".txt";
	outputFile="data/chat_sessions/"+s;
}

void writeToOF(string i){
    std::ofstream fs(outputFile,  std::ios_base::app);

    if(!fs)
    {
        std::cerr<<"Cannot open the output file."<<std::endl;
    }
    fs<<i+"\n";
    fs.close();
}
void readFile(string i){
    string x;
    ifstream inFile;
    inFile.open(i);
    if (!inFile)
        cout << "Unable to open file\n";
    while (getline(inFile,x))
    	cout << x << endl ;
    inFile.close();
}

void writeToCsv(int i, string j, int k, int l, double m){
    std::ofstream myfile;
    string IS = to_string(i)+","+j+","+to_string(k)+","+to_string(l)+","+to_string(m)+"\n";
    myfile.open (csvFile,  std::ios_base::app);
    myfile << IS;
    myfile.close();
}

void readCsv(int rownum)
{
    ifstream myFile;
    myFile.open(csvFile);
    string line;
    int a = 0;//counter


    while (getline(myFile, line)) {
        a++;
        if (a == rownum) {
        	row.clear();
        	string tmp;
        	stringstream ss(line);

        	while(getline(ss, tmp, ',')){
        	    row.push_back(tmp);
        	}
        }
    }
    myFile.close();
}

void summary(bool totalSummary, int sNum ){
	if(!totalSummary){
		readCsv(sNum+1);
		cout << "Chat "+to_string(sNum)+" has user asking "+row[2]+" times and system responding "+row[3]+" times. Total duration is "+row[4]+ " seconds." << endl;
	}
	else{
		int numOfRuns=0,userU=0,sysU=0;
		double time=0.0;
	    std::string line;
	    std::ifstream myfile(csvFile);
	    while (getline(myfile, line))
	        numOfRuns++;

	    for(int i=1;i<numOfRuns;i++){
	    	readCsv(i+1);
	    	userU+=stoi(row[2]);
	    	sysU+=stoi(row[3]);
	    	time+=stod(row[4]);
	    }
	    myfile.close();
	    cout << "There are "+to_string(numOfRuns-1)+" chats to date with user asking "+to_string(userU)+" times and system responding "+to_string(sysU)+" times. Total duration is "+to_string(time)+" seconds."<<endl;
	}
}

void showChat(int i){
	try{
		if(i>=1){
			readCsv(i+1);
			readFile(row[1]);
		}
		else
			throw "Inputs must be numeric, nonzero, and positive to view the associated chat.";
	}catch (const char* msg) {
		cerr << msg << endl;
	}
}


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
				 else if(word == "COUN")	//county
					 r1.county = line;
				 else if(word == "DIST")	//district
					 r1.district = line;

				 else if(word == "NAME"){ //assumes 4 part name given: title, first, mid, last (this will soon be changed to accommodate 3 part names: title, first, last)
					 if(r1.aname.getFirstName() == "none" || r1.aname.getTitle() == "none" || r1.aname.getLastName() == "none" || r1.aname.getMidInit() == "none")
						 r1.aname.title = r1.aname.firstName = r1.aname.lastName = r1.aname.midInit = "";

					 	stringstream lineStream(line); //open the line stream, and use the position of the word to determine what part of the name it is
			 			int wordCount = 0;
			 			string temp;

			 			while (lineStream >> temp) {
			 				if(wordCount == 0)
			 					r1.aname.title = temp;
			 				else if(wordCount==1)
			 					r1.aname.firstName = temp;
			 				else if(wordCount==2)
			 					r1.aname.midInit = temp;
			 				else if(wordCount==3)
			 					r1.aname.lastName = temp;
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
				else if(word == "COMM"){
					 if(r1.getCommittees()=="none")
						 r1.committees = "";
					 r1.committees += line + "\n";
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


int main(int argc, char* argv[]){


	if(argc==1){

		std::time_t start_time = std::chrono::system_clock::to_time_t(start);

		ts = std::ctime(&start_time);
		generateFileName(ts);
		//get time, name output file as date_time.txt
		processInput();
		string x;
		cout<<"Welcome to the district 92 chatbot!" << endl;
		writeToOF("Welcome to the district 92 chatbot!");

		while(true){
			cout << "\nPlease enter your question!" << endl;
			writeToOF("\nPlease enter your question!");
			std::getline(cin, x);
			writeToOF(x);
			userUtterance++;
			//send user utterance to file
			std::for_each(x.begin(), x.end(), [](char & c) {c = ::tolower(c);});

			if(x=="quit"||x=="q"){
				cout<<"Thank you for using the district 92 chatbot! Goodbye!" << endl;
				writeToOF("Thank you for using the district 92 chatbot! Goodbye!");
				systemUtterance++;

				auto end = std::chrono::steady_clock::now();
				std::chrono::duration<double> diff_in_seconds = end - steadystart;

				ifstream file(csvFile);
				string line;
				while (getline(file, line))
					rownumber++;

				//session is over, write statistics to the csv log.
				writeToCsv(rownumber,outputFile,userUtterance,systemUtterance,diff_in_seconds.count());
				break;
			}
			cout << r1.processQuestion(x)<<endl;
			writeToOF(r1.processQuestion(x));
			systemUtterance++;
			//send system utterance to file
		}
	}
	else if(argc==2)
	{
		try{
			string x = argv[1];
			std::for_each(x.begin(), x.end(), [](char & c) {c = ::tolower(c);});
			if(regex_match(x, regex("(.*)summary(.*)"))){
				summary(true,1);
			}
			else
				throw"Check your arguments! The only acceptable singular argument is \"summary\"";
		}catch (const char* msg) {
		     cerr << msg << endl;
		}
	}
	else if(argc==3){
		string x = argv[1];
		std::for_each(x.begin(), x.end(), [](char & c) {c = ::tolower(c);});
		int numOfRuns=0;
		std::string line;
	    std::ifstream myfile(csvFile);
	    while (getline(myfile, line)){
	        numOfRuns++;
	    }


		try{
			if(regex_match(x, regex("(.*)showchat(.*)"))&&regex_match(x, regex("(.*)summary(.*)"))){
				if(!isdigit(*argv[2]))
					throw "Inputs must be numeric, nonzero, positive, and must match an existing chat log.";
				else{
					string s1(argv[2]);
					int arg = stod(s1);
					if(arg>numOfRuns-1)
						throw"There aren't that many chat sessions logged. Please choose a valid number.";
					summary(false,arg);
				}
			}
			else if(regex_match(x, regex("(.*)showchat(.*)"))){
				if(!isdigit(*argv[2]))
					throw "Inputs must be numeric, nonzero, positive, and must match an existing chat log.";
				else{
					string s1(argv[2]);
					int arg = stod(s1);
					if(arg>numOfRuns-1)
						throw"There aren't that many chat sessions logged. Please choose a valid number.";
					showChat(arg);
				}
			}
			else
				throw"Check your arguments! Something isn't adding up!";
		}catch (const char* msg) {
		     cerr << msg << endl;
		}
	}
	else
	{
		cout << "Invalid number of arguments!" << endl;
	}
	return 0;
}

