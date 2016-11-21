#include"atm.h"
#include<iostream>
using std::cout;
using std::endl;

//启动界面
void ATM::firstlogo() {
	system("color 1C");//设置窗口颜色
	cout << "\n\n\n\n";
	cout << "\t\t\t\t************************************************" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****_______________WELCOME TO ATM___________****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****_______________(1)SIGN UP_______________****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****_______________(2)SIGN IN_______________****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****_______________(3)EXIT__________________****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << "\t\t\t\t************************************************" << endl;
	cout << "\t\t\t\t****                                        ****" << endl;
	cout << endl << endl;
	cout << "\t\t\t\t\t\t              copyright c Scaactk";//win32 不支持输出版权符号,甚至写在注释中，在编译过程中都无法通过;
	cout << "\n";
	cout << "\t\t\t\t\t\t Please Input Option:" << endl;
}

//功能界面
void ATM::secondlogo() {
	system("cls");
	system("color 3B");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(1)Fetch Money_________****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(2)Deposit Money_______****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(3)Transfer Money______****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(4)Change Passwords____****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(5)Check Information___****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(6)Print Record________****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t****_______(7)Return Before_______****" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t**************************************" << endl;
	cout << "\t\t\t\t****                              ****" << endl;
	cout << "\t\t\t\t\t\t    copyright c Scaactk";
	cout << "\n";
	cout << "\t\t\t\t Please Input Option:" << endl;
	cout << "\t\t\t\t";
}
