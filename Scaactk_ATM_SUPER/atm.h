#pragma once

class ATM {
public:
	static void firstlogo();//静态成员函数，访问不需要对象名
	static void secondlogo();
	/*
	注：不要试图在头文件中定义(初始化)静态数据成员。
	在大多数的情况下，这样做会引起重复定义这样的错误。
	即使加上#ifndef #define #endif或者#pragma once也不行。 
	*/
};

