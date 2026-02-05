#define  _CRT_SECURE_NO_WARNINGS 1
#include"RBTree.h"


void test1()
{
	RBTree<int, int> t;
	t.Insert(make_pair(10, 10));
	t.Insert(make_pair(20, 20));
	t.Insert(make_pair(30, 30));
	t.Insert(make_pair(15, 15));
	t.Insert(make_pair(25, 25));
	auto result = t.Find(15);
	// 检查是否找到并使用结果
	if (result != nullptr)
	{
		cout << "找到: key=" << result->_kv.first
			<< ", value=" << result->_kv.second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
	bool balanced = t.IsBalanced();
	cout << "红黑树是否平衡: " << (balanced ? "是" : "否") << endl;
	t.InOrder();
}

int main()
{
	test1();
	return 0;
}