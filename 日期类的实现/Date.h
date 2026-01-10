#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//日期类的实现（对构造函数和重载运算符的回顾）
class Date {
public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month);

	//打印
	void DatePrint()const;

	//输入、输出
	friend ostream& operator<<(ostream& out, Date d);
	friend istream& operator>>(istream& in, Date &d);

	// 构造函数
	Date(int _year, int _month, int _day) {
		year = _year;
		month = _month;
		day = _day;
	}

	// 拷贝构造函数d2(d1)
	Date(const Date& d);

	//检查日期是否合法
	bool DateCheck();

	//重载操作符
	bool operator<(const Date& d)const;
	bool operator<=(const Date& d)const;
	bool operator>(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator==(const Date& d)const;
	bool operator!=(const Date& d)const;


	//d1 += 天数
	Date& operator+=(int _day);
	Date operator+(int _day)const;

	//d1 -= 天数
	Date& operator-=(int _day);
	Date operator-(int _day)const;


	// 前置++
	Date& operator++();

	// 后置++
	Date operator++(int);

	// 后置--
	Date operator--(int);

	// 前置--
	Date& operator--();

	//d1-d2
	int operator-(const Date& d);


private:
	int year;
	int month;
	int day;
};