#pragma once
//#include<stdafx.h>
//#define _CRT_SECURE_NO_DEPRECATE
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#include<iostream>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<time.h>
#include<Windows.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::cin;

namespace Scaactk {
	int Check_ID(int);
	int Get_Passwords();
	int Compare(int, int);
	int Check_Mon(double);
	//int Append_User(User&);
	int Get_ID();
	//int Get_Info();
	void Print_Record(string);
	//void Record(string);
	string Int_To_String(int);
	string Get_time();

	string getInfo(string _fileName, string _id);
	int splitString(char dst[][10], char* str, const char* spl);
	double charToDbl(char *p);
	int Time_show();
}

int Scaactk::Check_ID(int id) {
	string _name;
	int _id;
	int _pw;
	double _Mon;
	int _statue;

	ifstream infile("sql.txt", std::ios::in);
	if(infile.fail()) {
		std::cerr << "FAIL_TO_OPEN" << endl;
		return false;
	}
	while (infile) {
		infile >> _name >> _id >> _pw >> _Mon >> _statue;//按行读取

		if (_id == id) {
			cerr << "This ID has been used!" << endl;
			infile.close();
			return false;
		}
	}
	cout << "This ID can be used!" << endl;
	infile.close();
	return true;
}

int Scaactk::Get_Passwords() {
	char pin[7];
	int temp = 0;
	for (int i = 0; i < 6; i++) {
		pin[i] = _getch();
		cout << "*";
		temp *= 10;
		temp += pin[i] - '0';
	}
	_getch();
	return temp;//返回之前输入的pw
}

int Scaactk::Compare(int t1, int t2) {
	if (t1 == t2) {
		return true;
	}
	else {
		return false;
	}
}

int Scaactk::Check_Mon(double m) {
	if (m < 0) {
		cerr << "Eroor Number!" << endl;
		return false;
	}
	else {
		return true;
	}
}
 
int Scaactk::Get_ID() {
	int _inid;
	cout << "Please input ID:" << endl;
	cin >> _inid;
	return _inid;
}

void Scaactk::Print_Record(string id) {
	ifstream record(id.c_str(), std::ios::in);
	//如果用fstream 会出现意想不到的错误，推测是基于同时访问和读写的冲突
	string line;
	while (!record.eof()) {
		getline(record, line);
		std::cout << line << endl;
	}
	record.close();
}

string Scaactk::Int_To_String(int id) {
	char temp[100];
	_itoa_s(id, temp, 10);
	return (string)temp;
}

string Scaactk::Get_time() {
	//time_t t;
	//tm* local;
	//char buf[128];
	//t = time(NULL);
	//
	//local = localtime(&t);
	//strftime(buf, 64, "%Y_%m_%d %H:%M:%S", local);//格式化间时
	//return (string)buf;

	//localtime这个方法存在隐患,
	//localtime 返回一个tm指针，空间是由自己控制的
	//所以连续调用这个函数会出问题

	//这里用localtime_s 代替
	time_t t;
	time(&t);
	//定义两个存储变量
	struct tm tmTmp;
	char stTmp[64];
	//转化为tm结构
	localtime_s(&tmTmp, &t);

	//转化为字符串
	asctime_s(stTmp, &tmTmp);
	return (string)stTmp;
}




/*           一部分解析函数          */

string Scaactk::getInfo(string _fileName, string _id) {
	//	string temp;
	//	FILE *fp;
	//	ifstream infile(_fileName.c_str());
	//	while (getline(infile, temp));
	//	return temp;//以字符串的形式返回文件中的全部内容
	char temp[100];
	ifstream infile;
	string sp_id;
	string sp_pw;
	string sp_mon;
	infile.open(_fileName.c_str(), std::ios::in);
	if (!infile.fail()) {
		while (infile.getline(temp, 100, '\n')) {
			string temp1 = temp;
			char dst[5][10];//每行的不超过五个数据，每个长度不超过10
			int count = Scaactk::splitString(dst, temp, ",");
			sp_id = dst[0];//将分割出的id转化成string
			if (_id == sp_id) {
				//std::cout << temp1;
				//std::cout << dst[0];
				//std::cout << dst[1];
				infile.close();
				return temp1;
			}
		}
		infile.close();
		std::cerr << "NOT_FOUND_ID";
		return "NOT_FOUND_ID";
	}
	else {
		infile.close();
		std::cerr << "FAIE_TO_OPEN";
		return "FAIE_TO_OPEN";
	}
}

int Scaactk::splitString(char dst[][10], char* str, const char* spl) {
	int n = 0;//分割字符串，这个即为分割传入的那一行到char[]中
	char *buf;
	char* result = NULL;
	result = strtok_s(str, spl, &buf);
	while (result != NULL) {
		strcpy_s(dst[n++], result);
		result = strtok_s(NULL, spl, &buf);
	}
	return n;
}


//将带小数点的字符串转换为double
//另外可以使用sstream直接转换
//这里写一下练练手
double Scaactk::charToDbl(char* src) {
	char *p = src;//引用局部变量是个很好的习惯
	double temp = 0;

	while (*p != '\0'&&*p != '.') {
		temp *= 10;
		temp += (*p) - '0';//将字符转化为数字
		p++;
	}

	if (*p == '.') {
		double step = 0.1;
		p++;//跳过小数点
		while (*p != '\0') {
			temp += step*((*p) - '0');
			step /= 10;
			p++;
		}
	}
	return temp;
}

int Scaactk::Time_show() {
	string num[11] = { "0","一","二","三","四","五","六","七","八","九","十" };

	time_t t = time(0);
	char tyear[5];
	char tm[3];
	char td[3];
	char tH[3];
	char tM[3];

	char tAll[1024];//开辟足够大的空间 存储几种输出方式

	//这里是localtime懒得改了，因此只在dev版本中有这个

	//strftime(tAll, sizeof(tAll), "%Y %x %A %X \t", localtime(&t));

	puts(tAll);

	//strftime(tyear, sizeof(tyear), "%Y", localtime(&t));
	//strftime(tm, sizeof(tm), "%m", localtime(&t));
	//strftime(td, sizeof(td), "%d", localtime(&t));
	//strftime(tH, sizeof(tH), "%H", localtime(&t));
	//strftime(tM, sizeof(tM), "%M", localtime(&t));

	string result = "";

	// 格式化 年
	int year = 0;
	year = atoi(tyear);
	int y[4];

	y[0] = year / 1000;
	year %= 1000;
	y[1] = year / 100;
	year %= 100;
	y[2] = year / 10;
	year %= 10;
	y[3] = year / 1;
	result = num[y[0]] + num[y[1]] + num[y[2]] + num[y[3]] + "年";

	// 格式化 月
	int month = atoi(tm);
	int m[2];
	m[0] = month / 10;
	m[1] = month % 10;
	if (m[0] != 0)
	{
		result += num[m[0]];
		if (m[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += num[m[1]];
		}
	}
	else
	{
		result += num[m[1]];
	}
	result += "月";

	// 格式化 日
	int day = atoi(td);
	int d[2];
	d[0] = day / 10;
	d[1] = day % 10;
	if (d[0] != 0)
	{
		result += num[d[0]];
		if (d[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += num[d[1]];
		}
	}
	else
	{
		result += num[d[1]];
	}
	result += "日	";

	// 格式化 时
	int hour = atoi(tH);
	int H[2];
	H[0] = hour / 10;
	H[1] = hour % 10;
	if (H[0] != 0)
	{
		result += num[H[0]];
		if (d[1] == 0)
		{
			result += num[10];
		}
		else
		{
			result += "十" + num[H[1]];
		}
	}
	else
	{
		result += num[H[1]];
	}


	// 格式化 分
	int min = atoi(tM);

	if (min == 0)
	{
		result += "整";
	}
	else
	{
		result += "时";
		int M[2];

		M[0] = hour / 10;
		M[1] = hour % 10;
		if (M[0] != 0)
		{
			result += num[M[0]];
			if (d[1] == 0)
			{
				result += num[10];
			}
			else
			{
				result += "十" + num[M[1]];
			}
		}
		else
		{
			result += num[M[1]];
		}
	}

	result += "分";

	cout << result << endl;

	return 0;
}