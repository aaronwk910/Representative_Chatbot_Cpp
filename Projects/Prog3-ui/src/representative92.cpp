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
	string s = "Name: "+ aname.getFullName() + "\nHome Phone: "+ homephone.getPhoneNumber() + "\nBusiness Phone: "+ businessPhone.getPhoneNumber() +"\nHome Address: "+ homeAddress.getAddress() + "\nBusiness Address "+ businessAddress.getAddress() + "\nCounty: " + county;
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
	string r;
	try{
		//personal info questions
		if(!regex_match(x,regex("(.*)everything(.*)"))&&regex_match(x, regex("(.*)about(.*)")))
			r = answerQuestion("Personal Info:");

		//contact info questions
		else if((regex_match(x, regex("(.*)where(.*)"))&&regex_match(x, regex("(.*)live(.*)")))||(regex_match(x, regex("(.*)home(.*)"))&&regex_match(x, regex("(.*)address(.*)"))))
			r = answerQuestion("Contact Info: Home Address");
		else if((regex_match(x, regex("(.*)where(.*)"))&&regex_match(x, regex("(.*)work(.*)")))||((regex_match(x, regex("(.*)work(.*)"))||regex_match(x, regex("(.*)business(.*)")))&&regex_match(x, regex("(.*)address(.*)"))))
			r = answerQuestion("Contact Info: Business Address");
		else if((regex_match(x, regex("(.*)contact(.*)"))||regex_match(x, regex("(.*)touch(.*)"))))
			r = answerQuestion("Contact Info:");
		//phone numbers
		else if((regex_match(x, regex("(.*)call(.*)"))&&regex_match(x, regex("(.*)home(.*)")))||(regex_match(x, regex("(.*)home(.*)"))&&regex_match(x, regex("(.*)phone(.*)"))))
			r = answerQuestion("Contact Info: Home Phone");
		else if((regex_match(x, regex("(.*)call(.*)"))&&regex_match(x, regex("(.*)work(.*)")))||((regex_match(x, regex("(.*)work(.*)"))||regex_match(x, regex("(.*)business(.*)")))&&regex_match(x, regex("(.*)phone(.*)"))))
			r = answerQuestion("Contact Info: Business Phone");
		//name
		else if(regex_match(x, regex("(.*)name(.*)")))
			r = answerQuestion("Contact Info: Name");
		//county
		else if(regex_match(x, regex("(.*)county(.*)"))||regex_match(x, regex("(.*)region(.*)")))
			r = answerQuestion("Contact Info: Region");
		//committees
		else if(regex_match(x, regex("(.*)committee(.*)")))
			r = answerQuestion("Committees");

		//service questions
		else if(regex_match(x, regex("(.*)service(.*)")))
			r = answerQuestion("Service");

		//other
		else if(regex_match(x, regex("(.*)everything(.*)")))
			r = "\n"+answerQuestion("Contact Info:")+"\n\n"+answerQuestion("Personal Info:")+"\n"+answerQuestion("Service:");
		else if(regex_match(x, regex("(.*)hello(.*)"))||regex_match(x, regex("(.*)hi(.*)"))||regex_match(x, regex("(.*)hey(.*)")))
			r = "Hello!" ;
		else if(regex_match(x, regex("(.*)goodbye(.*)"))||regex_match(x, regex("(.*)bye(.*)")))
			r ="Goodbye!";
		else
			r = "Sorry! I don't know the answer to that!";
	} catch (regex_error &e) {
	     r = e.what();
	     r = "CODE IS: " +e.code();
	}
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
