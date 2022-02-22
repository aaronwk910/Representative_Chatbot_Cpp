/*
 * 	representative.cpp
 *  Created on: Feb 1, 2022
 *  Author: Aaron King
 */

#include "representative92.h"
#include <string>

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
string representative::getParty(){
	return party;
}
string representative::getPersonalInfo(){
	return personalInfo;
}
string representative::getContactInfo(){
	string s = "Name: "+ name.getFullName() + "\nHome Phone: "+ homephone.getPhoneNumber() + "\nBusiness Phone: "+ businessPhone.getPhoneNumber() +"\nHome Address: "+ homeAddress.getAddress() + "\nBusiness Address "+ businessAddress.getAddress() + "\nCounty: " + county;
	return s;
}
string representative::getDistrict(){
	return district;
}
string representative::getService(){
	return service;
}
representative::representative(){
	county = party = personalInfo = district = service = "none";

}
representative::~representative(){
	name.~name();
	homephone.~phoneNumber();
	businessPhone.~phoneNumber();
	businessAddress.~address();
	homeAddress.~address();
}
