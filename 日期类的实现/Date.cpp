#define  _CRT_SECURE_NO_WARNINGS 1
#include"Date.h"

// 获取某年某月的天数
int Date::GetMonthDay(int year, int month)
{
	assert(month > 0 && month<13);
	static int day[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
	{
		return 29;
	}
	return day[month];
}

//打印
void Date::DatePrint()const
{
	cout << year << " " << month << " " << day << endl;
}




// 拷贝构造函数d2(d1)
Date::Date(const Date& d)
{
	this->day = d.day;
	this->month = d.month;
	this->year = d.year;
	if (!(DateCheck()))
	{
		cout << "输入错误" << endl;
	}
}



//检查日期是否合法
bool Date::DateCheck()
{
	if (month < 1 || month>12)
	{
		return false;
	}
	else
	{
		int tmp = GetMonthDay(year, month);
		if (tmp < day||day<1)
		{
			return false;
		}
	}
	return true;
}


//重载操作符
bool Date::operator<(const Date& d)const
{
	if (this->year < d.year)
	{
		return true;
	}
	else if(this->year==d.year)
	{
		if (this->month < d.month)
		{
			return true;
		}
		else if(this->month==d.month)
		{
			return this->day < d.day;
		}
	}
	return false;
}

bool Date::operator<=(const Date& d)const
{
	return *this == d || *this < d;
}



bool Date::operator>(const Date& d)const
{
	//照样愚蠢
	//if (this->year > d.year)
	//{
	//	return true;
	//}
	//else if (this->year == d.year)
	//{
	//	if (this->month > d.month)
	//	{
	//		return true;
	//	}
	//	else if (this->month == d.month)
	//	{
	//		return this->day > d.day;
	//	}
	//}
	//return false;
	return !(*this <= d);
}

bool Date::operator>=(const Date& d)const
{
	return !(*this < d);
}


bool Date::operator==(const Date& d)const
{
	//愚蠢的写法
	//if (this->year == d.year)
	//{
	//	if (this->month == d.month)
	//	{
	//		if (this->day == d.day)
	//		{
	//			return true;
	//		}
	//	}
	//}
	//return true;
	return this->year == d.year 
		&& this->month == d.month 
		&& this->day == d.day;
}

bool Date::operator!=(const Date& d)const
{
	return !(*this == d);
}


//d1 += 天数
Date& Date::operator+=(int _day)
{
	//如果天数是负数
	if (_day < 0)
	{
		return *this -= -day;
	}

	day += _day;
	while (day>GetMonthDay(year,month))
	{
		day -= GetMonthDay(year, month);
		month++;
		if (month == 13)
		{
			month = 1;
			year++;
		}
	}
	return *this;
}


Date Date::operator+(int _day)const
{
	Date tmp(*this);
	tmp += _day;
	return tmp;

}


//d1 -= 天数
Date& Date::operator-=(int _day)
{
	if (_day < 0)
	{
		return *this += -_day;
	}

	day -= _day;
	while (day <= 0)
	{
		month--;
		if (month == 0)
		{
			month == 12;
			year--;
		}
		day += GetMonthDay(year, month);
	}
	return *this;
}


Date Date::operator-(int _day)const
{
	Date tmp(*this);
	tmp -= _day;
	return tmp;
}


// 前置++

Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// 后置++
Date Date::operator++(int)
{
	Date tmp = *this;
	++*this;
	return tmp;
}

// 后置--
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

// 前置--
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

//d1-d2
int Date::operator-(const Date& d)
{
	int num = 0;
	int flat = 1;
	Date max = *this;
	Date min = d;
	if (*this < d)
	{
		flat = -1;
		swap(max, min);
	}
	while (max != min)
	{
		min++;
		num++;
	}
	return num * flat;
}

//输入、输出
ostream& operator<<(ostream& out, Date d)
{
	out << d.year << "." << d.month << "." << d.day << endl;
	return out;
}
istream& operator>>(istream& in, Date &d)
{
	if (!(d.DateCheck()))
	{
		cout << "输入错误！请重新输入" << endl;
	}
	in >> d.year >> d.month >> d.day;
	return in;
}