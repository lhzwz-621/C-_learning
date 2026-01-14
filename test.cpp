#define  _CRT_SECURE_NO_WARNINGS 1
#include"string.h"

void test1()
{
	bit::string  s1("hello world");
	//cout << s1.c_str() << endl;
	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i] += 2;
	}
	cout << s1.c_str() << endl;
}
void test2()//了解const char*和char*，以及char*输出可以直接打印整个字符串
{
	const char* s = "hello";
	int len = strlen(s);
	char* s1 = new char[len + 1];
	strcpy(s1, s);
	cout << s1 << endl;
}

void test3()//测试模拟迭代器
{
	bit::string s2("hello world");
	bit::string::iterator it = s2.begin();
	while (it != s2.end())
	{
		cout << *it << " ";
		++it;
	}
}

void test4()
{
	bit::string s3("hello world");
	//s3.push_back('!');
	//s3 += 'm';
	//s3.insert(0, 'x');
	s3.insert(0, "ns");
	s3.erase(0, 6);
	cout << s3.c_str() << endl;
}

void test5()//查找
{
	bit::string s4("hello world");
	size_t i = s4.find('h');
	cout << i << endl;
	i = s4.find("world");
	cout << i << endl;

}

void test6()
{
	static const size_t npos = -1;
	bit::string s5("test.cpp.zip");
	size_t pos = 0;
	while (s5.find('.', pos) != npos)
	{
		pos = s5.find('.', pos);
		bit::string suffix = s5.substr(pos);
		cout << suffix.c_str() << endl;
		pos++;
	}
}
void test7()//重载测试
{
	bit::string s1("hello world");
	bit::string s2("hello world");
	//cout << (s1 < s2) << endl;
	//cout << (s1 == s2) << endl;
	//cout << s2 << endl;
	//cin >> s1;
	//cout << s1 << endl;
	bit::string s3; 
	s3 = s1;
	cout << s3 << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	return 0;
}