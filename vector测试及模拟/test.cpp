#define  _CRT_SECURE_NO_WARNINGS 1
#include"vector.h"

namespace bit
{
	void test1()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//for (size_t i = 0; i < v1.size(); i++)
		//{
		//	cout << v1[i] << " ";
		//}
		printVector(v1);
	}

	void test2()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(4);
		v1.push_back(5);
		//v1.insert(v1.begin(),100,1);
		//auto it=v1.erase(v1.begin());
		//删掉所有偶数
		auto it = v1.begin();
		while (it != v1.end())
		{
			if (*it % 2 == 0)
			{
				v1.erase(it);
			}
			else
			{
				++it;
			}
			
		}
		printVector(v1);
	}



	void test3()
	{
		vector<int> v2;
		v2.push_back(0);
		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(3);
		v2.push_back(4);
		v2.resize(10);
		printVector(v2);
		cout << v2[0] << endl;
	}

	void test4()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2 = v1;//调用拷贝构造函数
		vector<int>v3;
		v3 = v1;//调用赋值运算符重载
		printVector(v2);
		printVector(v3);
	}
	void test5()
	{
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2;
		v2.push_back(100);
		v2.push_back(200);
		v2.push_back(300);
		v2 = v1;
		printVector(v1);
		printVector(v2);
	}
	void test6()
	{
		vector<int> v(10u, 1);//10u表示无符号整数10，如果都是int类型，可能会有歧义              
		printVector(v);
	}
}


int main()
{
	//bit::test1();
	//bit::test2();
	//bit::test3();
	//bit::test4();
	//bit::test5();
	bit::test6();
	return 0;
}
