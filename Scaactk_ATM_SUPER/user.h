#pragma once
#include<string>

#ifndef _ATM_USER_
#define _ATM_USER_

using std::string;
class User {
protected:
	string name;
	int id;
	int pw;
	double Mon;
	int statue;
public:
	User();
	User(string, int, int, double, int);
	int count;
	friend class func;
};

#endif
