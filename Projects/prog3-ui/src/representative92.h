/*
 *  representative.h
 *  Created on: Feb 1, 2022
 *  Author: Aaron King
 */

#ifndef REPRESENTATIVE92_H_
#define REPRESENTATIVE92_H_
#include <string>


using namespace std;

class phoneNumber{
public:
	int areaCode;
	int remainder1;
	int remainder2;
	int getAreaCodeInt();
	string getAreaCodeStr();
	string getPhoneNumber();
	phoneNumber();
	virtual ~phoneNumber();

};

class name{
public:
	string midInit;
	string title;
	string firstName;
	string lastName;
	string getMidInit();
	string getTitle();
	string getFirstName();
	string getLastName();
	string getFullName();
	name();
	virtual ~name();
};

class address{
public:
	int zip;
	string streetAdd;
	string city;
	int getZipInt();
	string getZipStr();
	string getStreetAdd();
	string getCity();
	string getAddress();
	address();
	virtual ~address();
};

class representative{
public:
	name aname;
	phoneNumber homephone;
	phoneNumber businessPhone;
	address homeAddress;
	address businessAddress;
	string county;
	string district;
	string service;
	string personalInfo;
	string committees;
	string getCounty();
	string getCommittees();
	string getPersonalInfo();
	string getContactInfo();
	string getDistrict();
	string getService();
	string answerQuestion(string);
	string processQuestion(string);
	representative();
	virtual ~representative();
};



#endif /* REPRESENTATIVE92_H_ */
