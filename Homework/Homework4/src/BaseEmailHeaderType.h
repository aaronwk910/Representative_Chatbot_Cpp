/*
 * BaseEmailHeaderType.h
 *
 *  Created on: Feb 28, 2022
 *      Author: aaron
 */

#ifndef BASEEMAILHEADERTYPE_H_
#define BASEEMAILHEADERTYPE_H_
#include <string>

using namespace std;

class BaseEmailHeaderType {
public:
	BaseEmailHeaderType();
	virtual ~BaseEmailHeaderType();

	string received;
	string to;
	string from;
	string contentType;
	string date;
	string messageID;
	string replyTo;
	string subject;

};

class GmailHeaderType: public BaseEmailHeaderType {
public:
	GmailHeaderType();
	virtual ~GmailHeaderType();

	string contentTransferEncoding;
	string mimeVersion;


};

class OutlookHeaderType: public BaseEmailHeaderType{
public:
	OutlookHeaderType();
	virtual ~OutlookHeaderType();
	string cc;
	string acceptLanguage;
	string contentLanguage;
	string organization;
	string attach;
	string references;
	string threadTopic;
	string threadIndex;
	string authenticationResults;


};

#endif /* BASEEMAILHEADERTYPE_H_ */
