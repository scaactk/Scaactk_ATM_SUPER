#include"func.h"
#include"scaactk.h"
#include<iostream>
//#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<string>
#include<time.h>
#include<Windows.h>

using std::cin;
using std::fstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using std::ifstream;

func::func(User& _user) :user(_user) {

}

void func::Welcome() {
	while (1) {//设置重复进入此界面
		int choose;
		system("cls");//清屏
		ATM::firstlogo();//启动
		cout << "\t\t\t\t\t";
		cin >> choose;
		if (choose == 1) {
			Sign_Up();
		}
		else if (choose == 2) {
			Sign_In();
		}
		else if (choose == 3) {
			system("pause");
			exit(0);//正常退出程序
		}
	}
}

//注册
void func::Sign_Up() {
	User user1;
	system("cls");
	cout << "Please input the name: " << endl;
	cin >> user1.name;
	system("cls");
	cout << "Please input your ID(six number): " << endl;
	cin >> user1.id;
	system("cls");
	if (Scaactk::Check_ID(user1.id)) {//检查ID是否重复
		//system("cls");
		cout << "Please input the passwords:" << endl;
		user1.pw = Scaactk::Get_Passwords();
		system("cls");
		cout << "Please input the passwords again:" << endl;
		int temp_pw = Scaactk::Get_Passwords();
		if (Scaactk::Compare(user1.pw, temp_pw)) {//检查两次密码是否匹配
			system("cls");
			cout << "How much money do you want to deposit first: " << endl;
			cin >> user1.Mon;
			if (Scaactk::Check_Mon(user1.Mon)) {
				fstream append("sql.txt", std::ios::out | std::ios::app);
				if (append.fail()) {
					std::cerr << "FAIL_TO_OPEN";
					system("pause");
					return;
				}
				else {
					system("cls");
					cout << std::flush;//刷新stdin
					append << user1.name << " " << user1.id << " " << user1.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user1.Mon << " " << 0 << endl;//向临时文件中写入指定行
					//cout << user1.name << " " << user1.id << " " << user1.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user1.Mon << " " << 0 << endl;//测试
					cout << "This User has been build!" << endl;
					append.close();

					//记录操作
					string rec = Scaactk::Int_To_String(user1.id);
					//time_t nowtime;
					//nowtime = time(NULL);
					ofstream record(rec.c_str(), std::ios::out|std::ios::app);
					record << user1.name << " " << Scaactk::Get_time() << " sign up" << endl;
					record.close();

					system("pause");
					return;
				}
			}
		}
		else {
			cerr << "Two passwords do not match!" << endl;
			system("pause");
			return;
		}
	}
	cerr << "Fail to sign up!" << endl;
	system("pause");
	return;
}

//登录
void func::Sign_In() {
	system("cls");
	user.id = Scaactk::Get_ID();
	if (!Get_Info(user)) {//匹配ID
		system("pause");
		return;
	}

	Check_Passwords(user);//检测密码

	cout << "\nLogin in successed!" << endl;\

	//记录操作
	string rec = Scaactk::Int_To_String(user.id);
	//time_t nowtime;
	//nowtime = time(NULL);
	fstream record(rec.c_str(), std::ios::out|std::ios::app);
	record << user.name << " " << Scaactk::Get_time() << " SIGN IN" << endl;
	record.close();

	system("pause");
	while (1) {
		ATM::secondlogo();//进入功能选择界面
		int choose;
		cin >> choose;
		system("cls");
		if (choose == 1) {
			Fetch_Money(user);
		}
		else if (choose == 2) {
			Deposit_Money(user);
		}
		else if (choose == 3) {
			Transfer_Money(user);
		}
		else if (choose == 4) {
			Change_Passwords(user);
		}
		else if (choose == 5) {
			Check_Information(user);
		}
		else if (choose == 6) {
			Print_Record(user);
		}
		else if (choose == 7) {
			return;
		}
		else {
			return;
		}
	}
}

//取款
void func::Fetch_Money(User& _user) {
	system("cls");
	User& user = _user;
	cout << "Please input how much money do you wang to fetch: " << endl;
	int temp;
	cin >> temp;
	if (temp >= user.Mon) {
		cout << " Without enough money!" << endl;
		system("pause");
		return;
	}
	else if (temp < 0) {
		cout << "Wrong number!" << endl;
		system("pasuse");
		return;
	}
	else {
		user.Mon -= temp;
		Write_TXT(user);
		cout << "You have fetched :" << temp << endl;

		//记录操作
		string rec = Scaactk::Int_To_String(user.id);
		//time_t nowtime;
		//nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << Scaactk::Get_time() << " Fetched " << temp << endl;
		record.close();

		system("pause");
		return;
	}
}

//存款
void func::Deposit_Money(User& _user) {
	system("cls");
	User& user = _user;
	cout << "Please input how much money do you wang to draw: " << endl;
	int temp;
	cin >> temp;
	if (temp < 0) {
		cout << "Wrong number!" << endl;
		system("pasuse");
		return;
	}
	else {
		user.Mon += temp;
		Write_TXT(user);
		cout << "YOU have deposited : " << temp << endl;

		//记录操作
		string rec = Scaactk::Int_To_String(user.id);
		//time_t nowtime;
		//nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << Scaactk::Get_time() << " Deposited " << temp << endl;
		record.close();

		system("pause");
		return;
	}
}

//转账
void func::Transfer_Money(User& _user) {
	system("cls");
	User& user = _user;
	User user2;

	cout << "You try to transfer money!" << endl;
	user2.id = Scaactk::Get_ID();
	if (!Get_Info(user2)) {
		system("pause");
		return;
	}
	
	if (user2.id == user.id) {
		cerr<<"You cannot transfer to yourself!" << endl;
		system("pause");
		return;
	}

	cout << "How much money do you want to transfer:" << endl;
	int temp;
	cin >> temp;
	if (temp <= 0) {
		cerr << "Error money!" << endl;
		system("pause");
		return;
	}
	else if (temp > user.Mon) {
		cout << " Without enough money!" << endl;
		system("pause");
		return;
	}
	else {
		user.Mon -= temp;
		user2.Mon += temp;
		Write_TXT(user);
		Write_TXT(user2);
		cout << "Transfer successed!" << endl;
		cout << "You have transfered:" << temp << endl;

		//记录操作
		string rec = Scaactk::Int_To_String(user.id);
		//time_t nowtime;
		//nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << Scaactk::Get_time() << " Transfered " << temp << " to " << user2.name << endl;
		record.close();

		system("pause");
		return;
	}
}

//改密
void func::Change_Passwords(User& _user) {
	system("cls");
	User&user = _user;
	char temp1[7];
	char temp2[7];
	bool a = true;

	cout << "Please input the old passwords to confirm your identity!" << endl;
	Check_Passwords(user);//校验旧密码

	cout << "\nPlease input the new passwords: " << endl;
	for (int i = 0; i < 6; i++) {
		temp1[i] = _getch();
		cout << "*";
	}
	_getch();

	cout << "\nInput the new passwords again:" << endl;
	for (int i = 0; i < 6; i++) {
		temp2[i] = _getch();
		cout << "*";
	}
	_getch();

	//检查匹配
	for (int i = 0; i < 6; i++) {
		if (temp1[i] != temp2[i]) {
			a = false;
		}
	}
	if (!a) {
		cout << "Two passwords  do not match!" << endl;
		cout << "Fail to change the passwords!" << endl;
		system("pause");
		return;
	}
	else {
		int pin[6];
		int temp = 0;
		for (int i = 0; i < 6; i++) {
			temp *= 10;
			temp += pin[i];
		}
		if (temp == user.pw) {
			cerr << "The new passwords is similiar to the old one!" << endl;
			system("pause");
			return;
		}
		user.pw = temp;
		Write_TXT(user);
		cout << "Change passwords successed!" << endl;

		//记录操作
		string rec = Scaactk::Int_To_String(user.id);
		//time_t nowtime;
		//nowtime = time(NULL);
		fstream record(rec.c_str(), std::ios::out|std::ios::app);
		record << user.name << " " << Scaactk::Get_time() << " Changed  the Passwords " << endl;
		record.close();

		system("pause");
		return;
	}
}

//查看信息
void func::Check_Information(User& _user) {
	User& user = _user;
	system("cls");
	cout << "\t\t\t\t Your information: " << endl;
	cout << "\t\t ID: " << user.id;
	cout << "\t\t\t\t Name: " << user.name;
	cout << "\t\t\t\t Money: " << user.Mon;
	system("pause");
	return;
}

//打印记录
void func::Print_Record(User& _user) {
	User& user = _user;
	string temp = Scaactk::Int_To_String(user.id);
	Scaactk::Print_Record(temp);
	system("pause");
	return;
}


//返回上层
//void func::Return_Before() {
//	system("cls");
//	return;
//}



/*            独立于选择功能之外的底层操作                */

//检索ID对应信息
int func::Get_Info(User& _user) {

	User& user = _user;
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in);
	if (infile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	user.count = 0;
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;
		//cout << _name << '\t' << _id << '\t' << _pw << '\t' << _Mon << '\t' << _statue << endl;//测试能否正常读取
		user.count++;
		if (_id == user.id) {
			if (_statue == 1) {
				cerr << "Your account has been freazed!" << endl;
				return false;
			}
			user.name = _name;
			user.pw = _pw;
			user.Mon = _Mon;
			user.statue = _statue;
			cout << "The user is:" << " " << user.name << " " << user.id << endl;

			//count = infile.tellg();
			//cout << count << endl;
			//infile.seekg(count-count1, std::ios::cur);
			//count = infile.tellg();//记录这一行开头的位置
			infile.close();
			return true;
		}
	}
	cerr << "Without this account!" << endl;
	infile.close();
	return false;
}

//更新用户数据
int func::Write_TXT(User& _user) {
	User& user = _user;
	ifstream file("sql.txt", std::ios::in);
	ofstream outfile("sql2.txt", std::ios::out | std::ios::trunc);

	if (file.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	if (outfile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	string line;
	int n = 1;
/*
这里有个很严重的bug, file在读取到文件末尾(EOF)的时候，并不会立即返回true,
而是再读一遍,这时eofdbit才被设置,
并且设置其他的bit,如goodbit,
等下次调用eof时才返回true
也就是说,在这里最后的换行符会被读取两次

既然知道问题所在，那就好办了
*/
	while (getline(file, line)) {
		////解决方案之一,多加一个判断,但是好像没什么效果23333
		//if (file.fail()) {
		//	break;
		//}
		//getline(file, line);//读取sql中一行
		if (n != user.count ) {
			outfile << line << endl;//将非指定行输出到一个临时文件sql2中去
		}
		else if (n == user.count ) {
			outfile << user.name << " " << user.id << " " << user.pw << " " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << user.Mon << " " << user.statue << endl;//向临时文件中写入指定行
			cout << std::flush;
		}
		n++;
	}
	outfile.close();
	file.close();

	ofstream outfile2("sql.txt", std::ios::out | std::ios::trunc);
	ifstream file2("sql2.txt", std::ios::in);
	if (file2.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	if (outfile2.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}

	while (getline(file2, line)) {
		//解决方案二:直接在while中判断
		outfile2 << line << endl;
	}
	outfile2.close();
	file2.close();
	system("del sql2.txt");//删除临时文件
	cout << endl << user.name << "'s DATA＿UPDATED" << endl;
	return true;
}

//检验密码
int func::Check_Passwords(User& _user) {
	User& user = _user;
	for (int i = 0; i < 3; i++) {
		cout << "Please input the passwords:" << endl;
		int temp_pw = Scaactk::Get_Passwords();
		if (temp_pw != user.pw) {//匹配密码
			cout << "\nWrong Passwords!" << endl;
		}
		else {
			return true;
		}

		if (i == 2) {
			user.statue = 1;
			Write_TXT(user);
			cerr << "The account has been freezed!" << endl;

			//记录操作
			string rec = Scaactk::Int_To_String(user.id);
			//time_t nowtime;
			//nowtime = time(NULL);
			fstream record(rec.c_str(), std::ios::out);
			record << user.name << " " << Scaactk::Get_time() << " Has been Freezed "  << endl;
			record.close();

			system("pause");
			exit(-1);
		}
	}
	return false;
}

//记录操作