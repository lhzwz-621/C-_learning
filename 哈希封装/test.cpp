#define  _CRT_SECURE_NO_WARNINGS 1
#include"HashiTable.h"
#include"unordered_set.h"
#include"unordered_map.h"
#include<iostream>

namespace bit
{
	void test_set()
	{
		unordered_set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 3,3,15 };
		for (auto e : a)
		{
			s.Insert(e);
		}

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;

		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			// 不⽀持修改
			//*it += 1;

			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_map()
	{
		 unordered_map<string, string> dict;
		 dict.Insert({ "sort", "排序" });
		 dict.Insert({ "left", "左边" });
		 dict.Insert({ "right", "右边" });
		
		 dict["left"] = "左边，剩余";
		 dict["insert"] = "插⼊";
		 dict["string"];
		
		 unordered_map<string, string>::iterator it = dict.begin();
		 while (it != dict.end())
		 {
		 // 不能修改first，可以修改second
		 //it->first += 'x';
		 it->second += 'x';
		
		 cout << it->first << ":" << it->second << endl;
		 ++it;
		 }
		 cout << endl;
	}

}


int main()
{
	//测试哈希表
	bit::test_set();
	bit::test_map();
	return 0;
}