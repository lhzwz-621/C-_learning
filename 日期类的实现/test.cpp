#define  _CRT_SECURE_NO_WARNINGS 1
#include"Date.h"

void test1()
{
	Date d1(2024, 2, 29);
	//int s=d1.GetMonthDay(2024,2);
	//printf("%d ", s);
	Date d2(d1);
	d1.DatePrint();
}

void test2()
{
	Date d3(2025, 2, 22);
	Date d4(2025, 2, 22);
	if (d3 == d4)
	{
		cout << "d3==d4" << endl;
	}
	else
	{
		cout << "d3!=d4" << endl;
	}
}


void test3()
{
	Date d5(2025,2,23);
	d5 = d5 + 100;
	d5.DatePrint();
	d5 =d5-100;
	d5.DatePrint();
	d5--;
	d5.DatePrint();
	Date d6 = d5--;
	d5.DatePrint();
	d6.DatePrint();
}

void test4()
{
	Date d7(2023, 1, 12);
	Date d8(2025, 1, 13);
	int num = d7 - d8;
	cout << num << endl;
}
void test5()
{
	Date d9(2025, 1, 12);
	cin >> d9;
	cout << d9;
}


int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}