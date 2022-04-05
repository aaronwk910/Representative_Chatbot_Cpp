/*
 * 	representative.cpp
 *  Created on: Feb 1, 2022
 *  Author: Aaron King
 */

#include "representative92.h"
#include <string>
#include <regex>
#include <numeric>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;
int phoneNumber::getAreaCodeInt(){
	return areaCode;
}
string phoneNumber::getAreaCodeStr(){
	return to_string(areaCode);
}
string phoneNumber::getPhoneNumber(){ //return full phone number with correct formatting
	string ret = "(";
	ret += to_string(areaCode);
	ret += ")";
	ret += to_string(remainder1);
	ret += "-";
	ret += to_string(remainder2);
	return ret;
}
phoneNumber::phoneNumber(){
	areaCode = 999;
	remainder1 = 999;
	remainder2 = 9999;
}
phoneNumber::~phoneNumber(){

}

string name::getMidInit(){
	return midInit;
}
string name::getTitle(){
	return title;
}
string name::getFirstName(){
	return firstName;
}
string name::getLastName(){
	return lastName;
}
string name::getFullName(){
	return (title + " " + firstName + " " + midInit + " " + lastName);
}
name::name(){
	midInit = "none";
	title = "none";
	firstName = "none";
	lastName = "none";
}
name::~name(){

}

int address::getZipInt(){
	return zip;
}
string address::getZipStr(){
	return to_string(zip);
}
string address::getStreetAdd(){
	return streetAdd;
}
string address::getCity(){
	return city;
}
string address::getAddress(){
	string ret = "";
	ret += streetAdd;
	ret += " ";
	ret += city;
	ret += " South Carolina ";
	ret += to_string(zip);
	return ret;
}
address::address(){
	zip = 99999;
	streetAdd = "none";
	city = "none";
}
address::~address(){

}

string representative::getCounty(){
	return county;
}
string representative::getCommittees(){
	return committees;
}
string representative::getPersonalInfo(){
	return personalInfo;
}
string representative::getContactInfo(){
	string s = "Name: "+ aname.getFullName() + "\nHome Phone: "+ homephone.getPhoneNumber() + "\nBusiness Phone: "+ businessPhone.getPhoneNumber() +"\nHome Address: "+ homeAddress.getAddress() + "\nBusiness Address "+ businessAddress.getAddress();
	return s;
}
string representative::getDistrict(){
	return district;
}
string representative::getService(){
	return service;
}

string representative::answerQuestion(string i){
	string answer;
	transform(i.begin(), i.end(), i.begin(), ::tolower);
	regex personalInfo("(.*)(pers)(.*)"); //pers info
	regex contactInfo("(.*)(cont)(.*)"); // cont info
	regex name("(.*)(name)(.*)"); // name
	regex business("(.*)(business)(.*)"); // busi
	regex home("(.*)(home)(.*)"); // home
	regex address("(.*)(address)(.*)"); // addr
	regex phoneNumber("(.*)(phone)(.*)"); // phone
	regex service("(.*)(serv)(.*)"); // serv
	regex region("(.*)(region)(.*)");//region
	regex commit("(.*)(committee)(.*)");//committees

	try{
		if(regex_match(i, commit))
			answer = getCommittees();
		else if(regex_match(i, contactInfo)){
			if(regex_match(i, name))
				answer = aname.getFullName();
			else if(regex_match(i, region))
				answer = getCounty()+ " County";
			else if(regex_match(i, phoneNumber)){
				if(regex_match(i, business))
					answer = businessPhone.getPhoneNumber();
				else if(regex_match(i, home))
					answer = homephone.getPhoneNumber();
				else
					answer = "Business Phone: " + businessPhone.getPhoneNumber() + "\nHome Phone: " + homephone.getPhoneNumber();
			}
			else if(regex_match(i, name))
				answer = aname.getFullName();
			else if(regex_match(i, address)){
				if(regex_match(i, business))
					answer = businessAddress.getAddress();
				else if(regex_match(i, home))
					answer = homeAddress.getAddress();
				else
					answer= "Business Address: " + businessAddress.getAddress() + "\nHome Address: " + homeAddress.getAddress();
			}
			else
				answer = getContactInfo();
		}
		else if(regex_match(i, personalInfo))
			answer = getPersonalInfo();
		else if(regex_match(i, service))
			answer = getService();
		else
			answer= "Invalid Argument to answerQuestion(). Please enter a valid one.";
		return answer;
	}catch (regex_error &e) {
	     answer = e.what();
	     answer = "CODE IS: " + e.code();
	}
	return answer;
}



string representative::processQuestion(string x){//takes in queries and feeds the correct request to answerQuestion
	double currentRatio=0.0;
	int m = 0; //number of matches
	int t = 0; // total number of words in query. m/t will give match ratio
	string xcopy = x;
	string r = "empty";// the answer to return
		std::stringstream ss(x);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> words(begin, end);
		/*	while(!xcopy.empty()){ //separating the first word into its own string
			stringstream lineStream(xcopy);
			string word;
			lineStream >> word;
			words.push_back(word);
			size_t space_pos = xcopy.find(" ");    // removes the first word from the current line
			if (space_pos != std::string::npos) {
				xcopy = xcopy.substr(space_pos + 1);
			}
		}*/
		t=int(words.size());
	//check the words against regex for common queries and classify based on percent matched.

	for(int i=0;i<t;i++){
		if(regex_match(words[i], regex("(.*)tell(.*)"))||regex_match(words[i], regex("(.*)me(.*)"))||regex_match(words[i], regex("(.*)about(.*)"))||regex_match(words[i], regex("(.*)rep(.*)"))||regex_match(words[i], regex("(.*)the(.*)"))||regex_match(words[i], regex("(.*)my(.*)")))
			m++;
	}
	currentRatio=m/t;
	if(currentRatio>0.7)
		r = answerQuestion("Personal Info:");
	currentRatio = 0.0;
	m=0;

	for(int i=0;i<t;i++){
		if(regex_match(words[i], regex("(.*)where(.*)"))||regex_match(words[i], regex("(.*)live(.*)"))||regex_match(words[i], regex("(.*)does(.*)"))||regex_match(words[i], regex("(.*)rep(.*)"))||regex_match(words[i], regex("(.*)the(.*)"))||regex_match(words[i], regex("(.*)my(.*)")))
			m++;
	}
	currentRatio=m/t;
	if(currentRatio>0.7)
		r = answerQuestion("Contact Info: Home Address");
	currentRatio = 0.0;
	m=0;

	for(int i=0;i<t;i++){
		if(regex_match(words[i], regex("(.*)how(.*)"))||regex_match(words[i], regex("(.*)do(.*)"))||regex_match(words[i], regex("(.*)i(.*)"))||regex_match(words[i], regex("(.*)rep(.*)"))||regex_match(words[i], regex("(.*)the(.*)"))||regex_match(words[i], regex("(.*)my(.*)"))||regex_match(words[i], regex("(.*)contact(.*)")))
			m++;
	}
	currentRatio=m/t;
	if(currentRatio>0.7)
		r = answerQuestion("Contact Info:");
	currentRatio = 0.0;
	m=0;

	for(int i=0;i<t;i++){
		if(regex_match(words[i], regex("(.*)what(.*)"))||regex_match(words[i], regex("(.*)committee(.*)"))||regex_match(words[i], regex("(.*)is(.*)"))||regex_match(words[i], regex("(.*)rep(.*)"))||regex_match(words[i], regex("(.*)the(.*)"))||regex_match(words[i], regex("(.*)my(.*)"))||regex_match(words[i], regex("(.*)on(.*)")))
			m++;
	}
	currentRatio=m/t;
	if(currentRatio>0.7)
		r = answerQuestion("Committees");
	currentRatio = 0.0;
	m=0;

	for(int i=0;i<t;i++){
		if(regex_match(words[i], regex("(.*)tell(.*)"))||regex_match(words[i], regex("(.*)me(.*)"))||regex_match(words[i], regex("(.*)everything(.*)"))||regex_match(words[i], regex("(.*)rep(.*)"))||regex_match(words[i], regex("(.*)the(.*)"))||regex_match(words[i], regex("(.*)my(.*)"))||regex_match(words[i], regex("(.*)about(.*)")))
			m++;
	}
	currentRatio=m/t;
	if(currentRatio>0.7)
		r = "\n"+answerQuestion("Contact Info:")+"\n\n"+answerQuestion("Personal Info:")+"\n"+answerQuestion("Service:");
	currentRatio = 0.0;
	m=0;

	if(r=="empty")
		r="Sorry, no match found. Please rephrase and try again!";

	return r;
}


representative::representative(){
	county = committees = personalInfo = district = service = "none";

}
representative::~representative(){
	aname.~name();
	homephone.~phoneNumber();
	businessPhone.~phoneNumber();
	businessAddress.~address();
	homeAddress.~address();
}
