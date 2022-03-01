/*
 * EmailInformationExtractor.cpp
 *
 *  Created on: Feb 28, 2022
 *      Author: Aaron King
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <numeric>
#include "BaseEmailHeaderType.h"

using namespace std;
string inputFile;
string demand;
string output;
regex gmailreg("(.*)gmail(.*)");
regex outlookreg("(.*)outlook(.*)");

//commons regex bank
regex receivedreg("(.*)Received(.*)");
regex toreg("(.*)To(.)");
regex fromreg("(.*)From(.*)");
regex contypereg("(.*)Type(.*)");
regex transreg("(.*)Transfer(.*)");
regex ccreg("(.*)CC(.*)");
regex datereg("(.*)Date(.*)");
regex idreg("(.*)ID(.*)");
regex replytoreg("(.*)Reply-To(.*)");
regex subreg("(.*)Subject(.*)");

//gmail regex bank
regex encodereg("(.*)Encoding(.*)");
regex mimereg("(.*)MIME(.*)");

//outlook regex bank
regex alreg("(.*)Accept(.*)");
regex clreg("(.*)Content-Language(.*)");
regex orgreg("(.*)Organ(.*)");
regex attreg("(.*)Attach(.*)");
regex refreg("(.*)Refer(.*)");
regex topreg("(.*)Topic:(.*)");
regex indreg("(.*)Index(.*)");
regex authreg("(.*)Results(.*)");



void setVariables(string s, string i){
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	if(regex_match(s,gmailreg))
		inputFile = "data/gmail.txt";
	else if(regex_match(s,outlookreg))
		inputFile = "data/outlook.txt";
	else
		cout << "invalid first argument" << endl;
	transform(i.begin(), i.end(), i.begin(), ::tolower);
	demand = i;
}

void processInput()
{
	if(inputFile != "")
	{
		ifstream input (inputFile);
		string line;
		if(input.is_open())
		{

			if(regex_search(inputFile, gmailreg)){ //if its gmail
				GmailHeaderType h1;
				 while (getline(input, line)) {
					// Now parse each line
					stringstream lineStream(line);
					int wordCount = 0;
					string word;
					string linecopy = line.substr(line.find_first_of(" \t")+1);

					while (lineStream >> word) {
						if(wordCount == 0){
							 if(regex_match(word, receivedreg))
								 h1.received=linecopy;
							 else if(regex_match(word,toreg))
								 h1.to=linecopy;
							 else if(regex_match(word, fromreg))
								 h1.from=linecopy;
							 else if(regex_match(word, contypereg))
								 h1.contentType=linecopy;
							 else if(regex_match(word, transreg))
								 h1.contentTransferEncoding=linecopy;
							 else if(regex_match(word, datereg))
								 h1.date=linecopy;
							 else if(regex_match(word, idreg))
								 h1.messageID=linecopy;
							 else if(regex_match(word, replytoreg))
								 h1.replyTo=linecopy;
							 else if(regex_match(word, subreg))
								 h1.subject=linecopy;

							 //now match uncommon regex
							 else if(regex_match(word, encodereg))
								 h1.contentTransferEncoding=linecopy;
							 else if(regex_match(word, mimereg))
								 h1.mimeVersion=linecopy;
							 }
							 wordCount++;
						} // end - while
				 }
					   if(demand == "received:")
					      output+=h1.received;
					   else if(demand =="to:")
					      output+=h1.to;
					   else if(demand=="from:")
					   	  output+=h1.from;
					   else if(demand=="content-type:")
						  output+=h1.contentType;
					   else if(demand=="content-transfer-encoding:")
					   	   output+=h1.contentTransferEncoding;
					   else if(demand== "date:")
						   output+=h1.date;
					   else if(demand=="message-id:")
						   output+=h1.messageID;
					   else if(demand== "reply-to:"||demand=="in-reply-to")
						   output+=h1.replyTo;
					   else if (demand=="subject:")
						   output +=h1.subject;
					   else if (demand=="mime-version:")
						   output+=h1.mimeVersion;
					   else
						   cout << "invalid second parameter" <<endl;
				 }
			else if(regex_search(inputFile, outlookreg)){ //if its outlook
				OutlookHeaderType h2;
				 while (getline(input, line)) {
					// Now parse each line
					stringstream lineStream(line);
					int wordCount = 0;
					string word;
					string linecopy = line.substr(line.find_first_of(" \t")+1);

					while (lineStream >> word) {
						if(wordCount == 0){
							 if(regex_match(word, receivedreg))
								 h2.received+=linecopy;
							 else if(regex_match(word,toreg))
								 h2.to=linecopy;
							 else if(regex_match(word, fromreg))
								 h2.from=linecopy;
							 else if(regex_match(word, contypereg))
								 h2.contentType=linecopy;
							 else if(regex_match(word, ccreg))
								 h2.cc=linecopy;
							 else if(regex_match(word, datereg))
								 h2.date=linecopy;
							 else if(regex_match(word, idreg))
								 h2.messageID=linecopy;
							 else if(regex_match(word, replytoreg))
								 h2.replyTo=linecopy;
							 else if(regex_match(word, subreg))
								 h2.subject=linecopy;
							 //now outlook regex

							 else if(regex_match(word,alreg))
								 h2.acceptLanguage=linecopy;
							 else if(regex_match(word,clreg))
								 h2.contentLanguage=linecopy;
							 else if(regex_match(word, orgreg))
								 h2.organization=linecopy;
							 else if(regex_match(word, attreg))
								 h2.attach=linecopy;
							 else if(regex_match(word, refreg))
								 h2.references=linecopy;
							 else if(regex_match(word, topreg))
								 h2.threadTopic=linecopy;
							 else if(regex_match(word, indreg))
								 h2.threadIndex=linecopy;
							 else if(regex_match(word, authreg))
								 h2.authenticationResults=linecopy;
							 }
							 wordCount++;
						} // end - while
					}//end getline
				   if (demand=="received:")
				      output+=h2.received;
				   else if (demand=="to:")
				      output+=h2.to;
				   else if (demand=="from:")
				   	  output+=h2.from;
				   else if (demand=="content-type:")
					  output+=h2.contentType;
				   else if (demand=="cc:")
					   output+=h2.cc;
				   else if (demand=="date:")
					   output+=h2.date;
				   else if (demand=="message-id:")
					   output+=h2.messageID;
				   else if(demand=="in-reply-to"||demand=="reply-to:")
					   output+=h2.replyTo;
				   else if (demand=="subject:")
					   output +=h2.subject;
				   else if (demand=="accept-language:")
					   output +=h2.acceptLanguage;
				   else if (demand=="content-language:")
					   output +=h2.contentLanguage;
				   else if (demand=="x-ms-exchange-organization-scl:")
					   output+=h2.organization;
				   else if (demand=="x-ms-has-attach:")
					   output+=h2.attach;
				   else if (demand=="references:")
					   output+=h2.references;
				   else if (demand=="thread-topic:")
					   output+=h2.threadTopic;
				   else if (demand=="thread-index:")
					   output+=h2.threadIndex;
				   else if (demand=="authentication-results:")
					   output+=h2.authenticationResults;
				   else
					   cout << "invalid second parameter" <<endl;
				 }//end elseif
			cout <<output<<endl;
			input.close();
		}
		else
		{
			cout << "ERROR: Could not open input file. Check file name."<< endl;
		}
	}
	else
	{
		cout << "ERROR: No input file found!"<< endl;
	}
}//end processInput

int main(int argc, char *argv[]){
	  std::string current_exec_name = argv[0]; // Name of the current exec program
	  vector<string> arglist(argv+1, argv+2);
	  vector<string> arglist2(argv+2, argv+argc);
	  string x = accumulate(arglist.begin(), arglist.end(), string (""));
	  string y = accumulate(arglist2.begin(), arglist2.end(), string (""));

	  if (argc > 2) {
		  setVariables(x,y);
		  processInput();
	 }
	  else
		  cout << "No argument passed" << endl;
}


