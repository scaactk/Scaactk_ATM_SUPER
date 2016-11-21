#pragma once
#include"user.h"
#include"atm.h"
class func {
private:
	User& user;
public:
	func(User& _user);

//可见功能
	void Welcome();
	void Sign_Up();
	void Sign_In();
	void Fetch_Money(User&);
	void Deposit_Money(User&);
	void Transfer_Money(User&);
	void Change_Passwords(User&);
	void Check_Information(User&);
	void Print_Record(User&);

//底层操作
	int Get_Info(User&);
	int Write_TXT(User&);
	int Check_Passwords(User&);
	//void Record(User&);
};