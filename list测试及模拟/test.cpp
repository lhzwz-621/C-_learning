#define  _CRT_SECURE_NO_WARNINGS 1
#include"List.h"

namespace bit
{
	void test1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.insert(lt.begin(), 100);
		lt.erase(lt.begin());

		//按需实例化
		//不可修改
		print_container(lt);
		//可修改
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			*it += 10;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}


	void test2()
	{
		list<int> lt;
		lt.push_front(1);
		lt.push_front(2);
		lt.push_front(3);
		lt.push_front(4);
		//insert后迭代器不失效
		lt.insert(++lt.begin(), 20);
		print_container(lt);

		//erase后迭代器失效
		list<int>::iterator it = lt.begin();
		while(it!=lt.end())
		{
			if(*it %2==0)
			{
				it=lt.erase(it);
			}
			else
			{
				++it;
			}
		}
		print_container(lt);
	}

	void test3()
	{
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		list<int> lt2 = lt1;//拷贝构造函数
		print_container(lt2);
		list<int> lt3;
		lt3.push_back(10);
		lt3.push_back(20);
		lt3.push_back(30);
		lt3 = lt1;//赋值运算符重载
		print_container(lt3);
	}
}



int main()
{
	//bit::test1();
	//bit::test2();
	bit::test3();
	return 0;
}